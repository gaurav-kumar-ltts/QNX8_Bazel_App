#pragma once

#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

// Config for machine_sm's OperationMode Function Group (Field/Engineering),
// independent of the MachineState Function Group (STARTUP/RUNNING/SHUTDOWN)
// sm_main.cc already manages via EcuState/transition_allowed. Kept separate
// because the two are orthogonal axes with their own shared-memory signal
// and their own manifest, not two values of the same state.
namespace sm_config {

// A single manifest-managed process, e.g. sshd.
struct ManagedProcess {
    std::string name;
    std::string path;
    std::vector<std::string> args;
};

// diag_app writes the field(0x00)/engineering(0x01) mode byte it receives
// over UDS DID 0x1705 into `state_shm`; machine_sm polls it and reconciles
// the running processes against the manifest for whichever state is
// active - the same way Execution Management starts/stops a Function
// Group's Process list on a state transition.
struct OperationModeConfig {
    std::string state_shm{"/xnm_mode_state"};
    int poll_interval_ms{500};
    std::vector<ManagedProcess> field_processes;
    std::vector<ManagedProcess> engineering_processes;
};

struct SmConfig {
    OperationModeConfig operation_mode;
};

inline SmConfig load_config(const std::string &path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open config file: " + path);
    }

    nlohmann::json root;
    input >> root;

    SmConfig config;

    if (root.contains("operation_mode")) {
        const auto &om = root.at("operation_mode");
        config.operation_mode.state_shm = om.value("state_shm", config.operation_mode.state_shm);
        config.operation_mode.poll_interval_ms = om.value("poll_interval_ms", config.operation_mode.poll_interval_ms);

        auto load_processes = [](const nlohmann::json &states, const char *state_name) {
            std::vector<ManagedProcess> processes;
            if (!states.contains(state_name)) {
                return processes;
            }
            for (const auto &entry : states.at(state_name).value("processes", nlohmann::json::array())) {
                ManagedProcess proc;
                proc.name = entry.value("name", "");
                proc.path = entry.value("path", "");
                if (proc.name.empty() || proc.path.empty()) {
                    throw std::runtime_error("operation_mode process entry missing required 'name' or 'path'");
                }
                if (entry.contains("args")) {
                    for (const auto &arg : entry.at("args")) {
                        proc.args.push_back(arg.get<std::string>());
                    }
                }
                processes.push_back(std::move(proc));
            }
            return processes;
        };

        if (om.contains("states")) {
            const auto &states = om.at("states");
            config.operation_mode.field_processes = load_processes(states, "field");
            config.operation_mode.engineering_processes = load_processes(states, "engineering");
        }
    }

    return config;
}

// --config <path>, then $SM_CONFIG, then the usual on-target/dev-tree
// default locations.
inline std::string resolve_config_path(int argc, char **argv) {
    for (int i = 1; i < argc - 1; ++i) {
        if (std::string(argv[i]) == "--config") {
            return argv[i + 1];
        }
    }

    if (const char *env_config = std::getenv("SM_CONFIG")) {
        if (*env_config) {
            return env_config;
        }
    }

    const std::vector<std::string> candidates = {
        "/etc/machine_sm/sm_config.json",
        "./sm_config.json",
    };
    for (const auto &candidate : candidates) {
        if (std::filesystem::exists(candidate)) {
            return candidate;
        }
    }
    return {};
}

}  // namespace sm_config
