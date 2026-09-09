#include <dlt/dlt.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <csignal>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "sm_config.hpp"
#include "sm_process.hpp"

DLT_DECLARE_CONTEXT(msm_ctx);

enum class EcuState : uint8_t {
    STARTUP = 0,
    RUNNING = 1,
    SHUTDOWN = 2
};

constexpr const char* SHM_NAME = "/msm_shared_state";
std::atomic<EcuState> current_state{EcuState::STARTUP};

// Transition matrix: [current][target] = allowed
bool transition_allowed[3][3] = {
    {true,  true,  false},  // STARTUP → STARTUP, RUNNING, (X) SHUTDOWN
    {false, true,  true },  // RUNNING → (X) STARTUP, RUNNING, SHUTDOWN
    {false, false, true }   // SHUTDOWN → (X) STARTUP/RUNNING, SHUTDOWN
};

//FUTURE STATES:


// Restart	    Initiates system reboot, terminates running processes, and reinitializes the platform and applications.
// Sleep	    Enters low-power mode, suspends applications, and preserves system state for quick resume.
// Update	    Manages software updates, including installation, verification, and activation of new software versions.
// Diagnostic	Activates diagnostic mode for troubleshooting, logging, or system health checks.
// Safe	        Transitions to a fail-safe mode to ensure minimal functionality during critical errors or failures.

void write_state_to_shm(EcuState state) {
    DLT_LOG(msm_ctx, DLT_LOG_DEBUG, DLT_STRING("Opening shared memory for writing state"));
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd < 0) {
        DLT_LOG(msm_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to open shared memory"));
        return;
    }
    DLT_LOG(msm_ctx, DLT_LOG_DEBUG, DLT_STRING("Truncating shared memory to size of uint8_t"));
    ftruncate(fd, sizeof(uint8_t));
    DLT_LOG(msm_ctx, DLT_LOG_DEBUG, DLT_STRING("Mapping shared memory for writing"));
    void* ptr = mmap(0, sizeof(uint8_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        DLT_LOG(msm_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to map shared memory"));
        close(fd);
        return;
    }
    DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Writing state to shared memory"), DLT_UINT8(static_cast<uint8_t>(state)));
    *static_cast<uint8_t*>(ptr) = static_cast<uint8_t>(state);
    DLT_LOG(msm_ctx, DLT_LOG_DEBUG, DLT_STRING("Unmapping shared memory"));
    munmap(ptr, sizeof(uint8_t));
    DLT_LOG(msm_ctx, DLT_LOG_DEBUG, DLT_STRING("Closing shared memory file descriptor"));
    close(fd);
}

EcuState read_state_from_shm() {
    DLT_LOG(msm_ctx, DLT_LOG_DEBUG, DLT_STRING("Opening shared memory for reading state"));
    int fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (fd < 0) {
        DLT_LOG(msm_ctx, DLT_LOG_WARN, DLT_STRING("Failed to open shared memory for reading, returning default STARTUP state"));
        return EcuState::STARTUP;
    }
    DLT_LOG(msm_ctx, DLT_LOG_DEBUG, DLT_STRING("Mapping shared memory for reading"));
    void* ptr = mmap(0, sizeof(uint8_t), PROT_READ, MAP_SHARED, fd, 0);
    uint8_t val = 0;
    if (ptr != MAP_FAILED) {
        DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Reading state from shared memory"));
        val = *static_cast<uint8_t*>(ptr);
        DLT_LOG(msm_ctx, DLT_LOG_DEBUG, DLT_STRING("Unmapping shared memory"));
        munmap(ptr, sizeof(uint8_t));
    } else {
        DLT_LOG(msm_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to map shared memory for reading"));
    }
    DLT_LOG(msm_ctx, DLT_LOG_DEBUG, DLT_STRING("Closing shared memory file descriptor"));
    close(fd);
    DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Read state from shared memory"), DLT_UINT8(val));
    return static_cast<EcuState>(val);
}

void enforce_transition(EcuState new_state) {
    EcuState old_state = current_state.load();
    DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Attempting state transition"), 
            DLT_STRING("from"), DLT_UINT8(static_cast<uint8_t>(old_state)),
            DLT_STRING("to"), DLT_UINT8(static_cast<uint8_t>(new_state)));
    if (transition_allowed[(int)old_state][(int)new_state]) {
        DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Transition allowed, updating state"));
        current_state = new_state;
        DLT_LOG(msm_ctx, DLT_LOG_DEBUG, DLT_STRING("Writing new state to shared memory"));
        write_state_to_shm(new_state);
        switch (new_state) {
            case EcuState::STARTUP:
                DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Transitioned to STARTUP"));
                break;
            case EcuState::RUNNING:
                DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Transitioned to RUNNING"));
                break;
            case EcuState::SHUTDOWN:
                DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Transitioned to SHUTDOWN"));
                break;
        }
    } else {
        DLT_LOG(msm_ctx, DLT_LOG_WARN, DLT_STRING("Illegal transition rejected"), 
                DLT_STRING("from"), DLT_UINT8(static_cast<uint8_t>(old_state)),
                DLT_STRING("to"), DLT_UINT8(static_cast<uint8_t>(new_state)));
    }
}

void monitor_state_requests() {
    DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Starting state request monitoring thread"));
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        DLT_LOG(msm_ctx, DLT_LOG_DEBUG, DLT_STRING("Checking for state change in shared memory"));
        EcuState shm_state = read_state_from_shm();
        if (shm_state != current_state.load()) {
            DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Detected state change in shared memory"),
                    DLT_STRING("new state"), DLT_UINT8(static_cast<uint8_t>(shm_state)));
            enforce_transition(shm_state);
        }
    }
}

// ---------------------------------------------------------------------------
// OperationMode Function Group (Field/Engineering) - independent of the
// MachineState Function Group above. diag_app writes the mode byte it
// receives over UDS DID 0x1705 into its own shared-memory segment (separate
// from SHM_NAME/EcuState, so a diagnostic mode write can never be
// misinterpreted as a STARTUP/RUNNING/SHUTDOWN transition or bypass
// transition_allowed); this reconciles the manifest-listed Processes for
// whichever state is currently active, the same way EM starts/stops a
// Function Group's Process list on a state transition.
// ---------------------------------------------------------------------------

enum class OperationMode : uint8_t {
    FIELD = 0x00,
    ENGINEERING = 0x01
};

OperationMode read_operation_mode_from_shm(const std::string& shm_name) {
    int fd = shm_open(shm_name.c_str(), O_RDONLY, 0666);
    if (fd < 0) {
        // Not created yet (no tester has ever set the mode) - default to
        // field, the restrictive state.
        return OperationMode::FIELD;
    }
    void* ptr = mmap(0, sizeof(uint8_t), PROT_READ, MAP_SHARED, fd, 0);
    uint8_t val = 0;
    if (ptr != MAP_FAILED) {
        val = *static_cast<uint8_t*>(ptr);
        munmap(ptr, sizeof(uint8_t));
    }
    close(fd);
    return val == static_cast<uint8_t>(OperationMode::ENGINEERING) ? OperationMode::ENGINEERING : OperationMode::FIELD;
}

// Tracks the Processes currently running for the OperationMode FG, keyed by
// name, and reconciles them against a state's manifest each tick. Called
// every poll regardless of whether the mode changed, so it also self-heals
// a process that crashed while its state was still active.
class OperationModeSupervisor {
public:
    void reconcile(const std::vector<sm_config::ManagedProcess>& desired) {
        reap_exited();

        std::set<std::string> desired_names;
        for (const auto& proc : desired) {
            desired_names.insert(proc.name);
        }

        for (auto it = running_.begin(); it != running_.end();) {
            if (desired_names.count(it->first) == 0) {
                sm_process::terminate(msm_ctx, it->first, it->second);
                it = running_.erase(it);
            } else {
                ++it;
            }
        }

        for (const auto& proc : desired) {
            if (running_.count(proc.name) != 0) {
                continue;
            }
            const pid_t pid = sm_process::spawn_detached(msm_ctx, proc.path, proc.args);
            if (pid > 0) {
                running_[proc.name] = pid;
            } else {
                DLT_LOG(msm_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to start managed process:"), DLT_STRING(proc.name.c_str()));
            }
        }
    }

private:
    void reap_exited() {
        for (auto it = running_.begin(); it != running_.end();) {
            if (sm_process::has_exited(it->second)) {
                DLT_LOG(msm_ctx, DLT_LOG_WARN, DLT_STRING("Managed process exited unexpectedly:"), DLT_STRING(it->first.c_str()));
                it = running_.erase(it);
            } else {
                ++it;
            }
        }
    }

    std::map<std::string, pid_t> running_;
};

void monitor_operation_mode(const sm_config::OperationModeConfig& cfg) {
    DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Starting OperationMode FG monitoring thread"), DLT_STRING(cfg.state_shm.c_str()));
    OperationModeSupervisor supervisor;
    while (true) {
        const OperationMode mode = read_operation_mode_from_shm(cfg.state_shm);
        const auto& desired = mode == OperationMode::ENGINEERING ? cfg.engineering_processes : cfg.field_processes;
        supervisor.reconcile(desired);
        std::this_thread::sleep_for(std::chrono::milliseconds(cfg.poll_interval_ms));
    }
}

int main(int argc, char** argv) {
    DLT_REGISTER_APP("MSM", "Machine State Manager");
    DLT_REGISTER_CONTEXT(msm_ctx, "MSMC", "State Mgmt w/ Table");

    DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Initializing Machine State Manager"));
    DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("[TIMING] Application Starting..."));

    DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Enforcing initial STARTUP state"));
    enforce_transition(EcuState::STARTUP);
    DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Starting state monitoring thread"));
    std::thread monitor(monitor_state_requests);

    // OperationMode FG is optional: a missing/invalid manifest shouldn't
    // take down MachineState monitoring, which is the more fundamental duty
    // of this process.
    const std::string config_path = sm_config::resolve_config_path(argc, argv);
    if (config_path.empty()) {
        DLT_LOG(msm_ctx, DLT_LOG_WARN, DLT_STRING("No sm_config.json found; OperationMode FG (sshd gating) disabled"));
    } else {
        try {
            const sm_config::SmConfig config = sm_config::load_config(config_path);
            std::thread op_mode_monitor(monitor_operation_mode, config.operation_mode);
            op_mode_monitor.detach();
        } catch (const std::exception& ex) {
            DLT_LOG(msm_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to load sm_config.json, OperationMode FG disabled:"), DLT_STRING(ex.what()));
        }
    }

    monitor.join();

    DLT_LOG(msm_ctx, DLT_LOG_INFO, DLT_STRING("Shutting down Machine State Manager"));
    DLT_UNREGISTER_CONTEXT(msm_ctx);
    DLT_UNREGISTER_APP();
    DLT_LOG(msm_ctx, DLT_LOG_DEBUG, DLT_STRING("Unlinking shared memory"));
    shm_unlink(SHM_NAME);
    return 0;
}
