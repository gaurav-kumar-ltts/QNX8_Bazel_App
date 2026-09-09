#pragma once

#include <cstdint>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace xnm_config {

struct PhysicalInterfaceConfig {
    std::string name;
};

struct InterfaceConfig {
    std::string name;
    std::string parent;
    std::uint16_t vlan_id{0};
    std::string mode{"static"};  // "static" or "dhcp"
    std::string ip;
    std::string netmask;
};

struct FirewallConfig {
    std::string rules_file;
    bool enable{false};
};

struct XnmConfig {
    std::vector<PhysicalInterfaceConfig> physical_interfaces;
    std::vector<InterfaceConfig> interfaces;
    FirewallConfig firewall;
};

inline XnmConfig load_config(const std::string &path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open config file: " + path);
    }

    nlohmann::json root;
    input >> root;

    XnmConfig config;

    if (root.contains("physical_interfaces")) {
        for (const auto &entry : root.at("physical_interfaces")) {
            PhysicalInterfaceConfig phys;
            phys.name = entry.value("name", "");
            if (phys.name.empty()) {
                throw std::runtime_error("physical_interfaces entry missing required 'name'");
            }
            config.physical_interfaces.push_back(std::move(phys));
        }
    }

    if (root.contains("interfaces")) {
        for (const auto &entry : root.at("interfaces")) {
            InterfaceConfig iface;
            iface.name = entry.value("name", "");
            iface.parent = entry.value("parent", "");
            iface.vlan_id = entry.value("vlan_id", 0);
            iface.mode = entry.value("mode", "static");
            iface.ip = entry.value("ip", "");
            iface.netmask = entry.value("netmask", "");

            if (iface.name.empty() || iface.parent.empty()) {
                throw std::runtime_error("Interface entry missing required 'name' or 'parent'");
            }
            if (iface.mode != "static" && iface.mode != "dhcp") {
                throw std::runtime_error("Interface '" + iface.name + "' has invalid mode '" + iface.mode +
                                          "' (expected 'static' or 'dhcp')");
            }
            if (iface.mode == "static" && (iface.ip.empty() || iface.netmask.empty())) {
                throw std::runtime_error("Interface '" + iface.name + "' has mode 'static' but is missing 'ip' or 'netmask'");
            }

            config.interfaces.push_back(std::move(iface));
        }
    }

    if (root.contains("firewall")) {
        const auto &fw = root.at("firewall");
        config.firewall.rules_file = fw.value("rules_file", "");
        config.firewall.enable = fw.value("enable", false);
    }

    return config;
}

}

