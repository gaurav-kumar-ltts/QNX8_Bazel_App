#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <net/if.h>

#ifdef __QNXNTO__
#include <net/if_vlan_var.h>
#endif

#include <dlt/dlt.h>

#include "xnm_config.hpp"

DLT_DECLARE_CONTEXT(xnm_ctx);

namespace {

std::string join_args(const std::vector<std::string> &args) {
    std::string joined;
    for (const auto &a : args) {
        if (!joined.empty()) {
            joined += " ";
        }
        joined += a;
    }
    return joined;
}

// Runs an external tool (ifconfig/pfctl) and waits for it to finish.
// Returns the process exit code, or -1 if it could not be started/waited on.
int run_command(const std::vector<std::string> &args) {
    DLT_LOG(xnm_ctx, DLT_LOG_INFO, DLT_STRING("Running:"), DLT_STRING(join_args(args).c_str()));

    std::vector<char *> argv;
    argv.reserve(args.size() + 1);
    for (const auto &a : args) {
        argv.push_back(const_cast<char *>(a.c_str()));
    }
    argv.push_back(nullptr);

    const pid_t pid = fork();
    if (pid < 0) {
        DLT_LOG(xnm_ctx, DLT_LOG_ERROR, DLT_STRING("fork() failed:"), DLT_STRING(strerror(errno)));
        return -1;
    }
    if (pid == 0) {
        execvp(argv[0], argv.data());
        _exit(127);
    }

    int status = 0;
    if (waitpid(pid, &status, 0) < 0) {
        DLT_LOG(xnm_ctx, DLT_LOG_ERROR, DLT_STRING("waitpid() failed:"), DLT_STRING(strerror(errno)));
        return -1;
    }
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return -1;
}

#ifdef __QNXNTO__

bool interface_exists(const std::string &name) {
    const int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        return false;
    }
    struct ifreq ifr {};
    std::strncpy(ifr.ifr_name, name.c_str(), IFNAMSIZ - 1);
    const int rc = ioctl(fd, SIOCGIFFLAGS, &ifr);
    close(fd);
    return rc == 0;
    
}

bool interface_is_up(const std::string &name) {
    const int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        return false;
    }
    struct ifreq ifr {};
    std::strncpy(ifr.ifr_name, name.c_str(), IFNAMSIZ - 1);
    const int rc = ioctl(fd, SIOCGIFFLAGS, &ifr);
    close(fd);
    if (rc != 0) {
        return false;
    }
    return (ifr.ifr_flags & IFF_UP) != 0;
}

// Queries the current VLAN parent/tag for an interface directly via the
// SIOCGETVLAN ioctl, without shelling out to ifconfig.
bool get_vlan_info(const std::string &name, std::string &parent_out, std::uint16_t &tag_out) {
    const int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        return false;
    }
    struct ifreq ifr {};
    struct vlanreq vreq {};
    std::strncpy(ifr.ifr_name, name.c_str(), IFNAMSIZ - 1);
    ifr.ifr_data = reinterpret_cast<caddr_t>(&vreq);
    const int rc = ioctl(fd, SIOCGETVLAN, &ifr);
    close(fd);
    if (rc != 0) {
        return false;
    }
    parent_out = vreq.vlr_parent;
    tag_out = vreq.vlr_tag;
    return true;
}

#else

// Non-QNX hosts don't have the SIOCGETVLAN/vlanreq ioctl interface; these
// stubs let the tool still build elsewhere, but VLAN state is never queried.
bool interface_exists(const std::string &) { return false; }
bool interface_is_up(const std::string &) { return false; }
bool get_vlan_info(const std::string &, std::string &, std::uint16_t &) { return false; }

#endif

// At boot, xnm_app runs immediately after net_start.sh brings io-sock up, but
// the physical NIC driver can still be enumerating/negotiating link for a
// few seconds after that. The interface can exist (SIOCGIFFLAGS succeeds)
// before it's actually ready to be brought up, so repeatedly retry
// "ifconfig <name> up" itself and check IFF_UP, rather than issuing it once
// right after the interface first appears.
bool wait_for_interface_up(const std::string &name, int timeout_ms = 10000, int poll_ms = 200) {
    for (int waited_ms = 0;; waited_ms += poll_ms) {
        if (interface_exists(name)) {
            run_command({"ifconfig", name, "up"});
            if (interface_is_up(name)) {
                return true;
            }
        }
        if (waited_ms >= timeout_ms) {
            return false;
        }
        usleep(static_cast<useconds_t>(poll_ms) * 1000);
    }
}

// Brings up a physical trunk interface with no IP of its own, and makes sure
// dhcpcd hasn't opportunistically grabbed an address on it (see dhcpcd.conf's
// allowinterfaces scoping, which is the primary fix for this).
bool apply_physical_interface(const xnm_config::PhysicalInterfaceConfig &cfg) {
    const bool ok = wait_for_interface_up(cfg.name);
    run_command({"dhcpcd", "-k", cfg.name});

    if (ok) {
        DLT_LOG(xnm_ctx, DLT_LOG_INFO, DLT_STRING("Physical interface up:"), DLT_STRING(cfg.name.c_str()));
        std::cerr << "xnm_app: physical interface up: " << cfg.name << std::endl;
    } else {
        DLT_LOG(xnm_ctx, DLT_LOG_ERROR, DLT_STRING("Timed out waiting for physical interface to come up:"), DLT_STRING(cfg.name.c_str()));
        std::cerr << "xnm_app: TIMED OUT waiting for physical interface to come up: " << cfg.name << std::endl;
    }
    return ok;
}

bool apply_interface(const xnm_config::InterfaceConfig &cfg) {
    if (!interface_exists(cfg.name)) {
        DLT_LOG(xnm_ctx, DLT_LOG_INFO, DLT_STRING("Interface does not exist, creating:"), DLT_STRING(cfg.name.c_str()));
        run_command({"ifconfig", cfg.name, "create"});
    }

    // SIOCSETVLAN refuses to re-tag an interface that's already up with the
    // same (or different) VLAN config ("Resource busy"), so only touch it if
    // it doesn't already match what we want. This makes re-running xnm_app
    // against an already-configured interface a no-op instead of an error.
    std::string existing_parent;
    std::uint16_t existing_tag = 0;
    const bool vlan_already_set =
        get_vlan_info(cfg.name, existing_parent, existing_tag) && existing_parent == cfg.parent && existing_tag == cfg.vlan_id;

    if (!vlan_already_set) {
        run_command({"ifconfig", cfg.name, "down"});
        run_command({"ifconfig", cfg.name, "vlan", std::to_string(cfg.vlan_id), "vlandev", cfg.parent});
    }

    if (cfg.mode == "dhcp") {
        run_command({"ifconfig", cfg.name, "up"});
        run_command({"dhcpcd", cfg.name});
    } else {
        run_command({"ifconfig", cfg.name, "inet", cfg.ip, "netmask", cfg.netmask, "up"});
        // Defensive: make sure dhcpcd hasn't also grabbed an address here.
        // dhcpcd.conf's allowinterfaces scoping is the real fix; this just
        // cleans up if it raced us before that scoping took effect.
        run_command({"dhcpcd", "-k", cfg.name});
    }

    std::string actual_parent;
    std::uint16_t actual_tag = 0;
    const bool have_vlan_info = get_vlan_info(cfg.name, actual_parent, actual_tag);
    const bool up = interface_is_up(cfg.name);
    const bool ok = have_vlan_info && actual_parent == cfg.parent && actual_tag == cfg.vlan_id && up;

    if (ok) {
        DLT_LOG(xnm_ctx, DLT_LOG_INFO, DLT_STRING("Interface configured OK:"), DLT_STRING(cfg.name.c_str()),
                DLT_STRING("mode"), DLT_STRING(cfg.mode.c_str()), DLT_STRING("vlan"), DLT_UINT16(actual_tag),
                DLT_STRING("parent"), DLT_STRING(actual_parent.c_str()));
        std::cerr << "xnm_app: interface configured OK: " << cfg.name << " mode=" << cfg.mode
                  << " vlan=" << actual_tag << " parent=" << actual_parent << std::endl;
    } else {
        DLT_LOG(xnm_ctx, DLT_LOG_ERROR, DLT_STRING("Interface verification failed for:"), DLT_STRING(cfg.name.c_str()));
        std::cerr << "xnm_app: FAILED to verify interface: " << cfg.name
                  << " (exists+vlan_info=" << have_vlan_info << " parent=" << actual_parent
                  << " tag=" << actual_tag << " up=" << up << ", wanted parent=" << cfg.parent
                  << " tag=" << cfg.vlan_id << ")" << std::endl;
    }
    return ok;
}

bool apply_firewall(const xnm_config::FirewallConfig &fw) {
    bool ok = true;

    if (!fw.rules_file.empty()) {
        const int rc = run_command({"pfctl", "-f", fw.rules_file});
        if (rc != 0) {
            DLT_LOG(xnm_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to load pf rules from:"), DLT_STRING(fw.rules_file.c_str()),
                    DLT_STRING("exit code"), DLT_INT(rc));
            ok = false;
        } else {
            DLT_LOG(xnm_ctx, DLT_LOG_INFO, DLT_STRING("Loaded pf rules from:"), DLT_STRING(fw.rules_file.c_str()));
        }
    }

    if (fw.enable) {
        const int rc = run_command({"pfctl", "-e"});
        // pfctl -e exits non-zero when pf is already enabled; only a missing
        // binary (execvp fallback exit code 127) is a real failure here.
        if (rc == 127) {
            DLT_LOG(xnm_ctx, DLT_LOG_ERROR, DLT_STRING("pfctl not found; cannot enable firewall"));
            ok = false;
        } else {
            DLT_LOG(xnm_ctx, DLT_LOG_INFO, DLT_STRING("pf enable requested, pfctl exit code:"), DLT_INT(rc));
        }
    }

    return ok;
}

std::string resolve_config_path(int argc, char **argv) {
    for (int i = 1; i < argc - 1; ++i) {
        if (std::string(argv[i]) == "--config") {
            return argv[i + 1];
        }
    }

    if (const char *env_config = std::getenv("XNM_CONFIG")) {
        if (*env_config) {
            return env_config;
        }
    }

    const std::vector<std::string> candidates = {
        "/etc/xnm/xnm_config.json",
        "./xnm_config.json",
    };
    for (const auto &candidate : candidates) {
        if (std::filesystem::exists(candidate)) {
            return candidate;
        }
    }
    return {};
}

}  // namespace

int main(int argc, char **argv) {
    DLT_REGISTER_APP("XNMA", "XNM Network Manager");
    DLT_REGISTER_CONTEXT(xnm_ctx, "XCTX", "XNM Context");

    const std::string config_path = resolve_config_path(argc, argv);
    if (config_path.empty()) {
        DLT_LOG(xnm_ctx, DLT_LOG_ERROR, DLT_STRING("No config file found (use --config <path> or XNM_CONFIG)"));
        std::cerr << "xnm_app: no config file found (use --config <path> or XNM_CONFIG)" << std::endl;
        DLT_UNREGISTER_CONTEXT(xnm_ctx);
        DLT_UNREGISTER_APP();
        return EXIT_FAILURE;
    }

    DLT_LOG(xnm_ctx, DLT_LOG_INFO, DLT_STRING("Loading config:"), DLT_STRING(config_path.c_str()));

    bool all_ok = true;
    try {
        const xnm_config::XnmConfig config = xnm_config::load_config(config_path);

        for (const auto &phys : config.physical_interfaces) {
            if (!apply_physical_interface(phys)) {
                all_ok = false;
            }
        }

        for (const auto &iface : config.interfaces) {
            if (!apply_interface(iface)) {
                all_ok = false;
            }
        }

        if (!apply_firewall(config.firewall)) {
            all_ok = false;
        }
    } catch (const std::exception &ex) {
        DLT_LOG(xnm_ctx, DLT_LOG_ERROR, DLT_STRING("Fatal error:"), DLT_STRING(ex.what()));
        std::cerr << "xnm_app: " << ex.what() << std::endl;
        all_ok = false;
    }

    std::cerr << "xnm_app: finished, overall status = " << (all_ok ? "OK" : "FAILED") << std::endl;

    DLT_UNREGISTER_CONTEXT(xnm_ctx);
    DLT_UNREGISTER_APP();
    return all_ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
