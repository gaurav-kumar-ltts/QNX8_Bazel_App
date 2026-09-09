#pragma once

#include <cerrno>
#include <csignal>
#include <cstring>
#include <string>
#include <vector>

#include <sys/wait.h>
#include <unistd.h>

#include <dlt/dlt.h>

// Process-spawning helpers for machine_sm's OperationMode Function Group
// (starting/stopping manifest-listed Processes like sshd on a Field <->
// Engineering transition).
namespace sm_process {

inline std::string join_args(const std::vector<std::string> &args) {
    std::string joined;
    for (const auto &a : args) {
        if (!joined.empty()) {
            joined += " ";
        }
        joined += a;
    }
    return joined;
}

// Starts a long-running process (e.g. sshd -D) and returns its pid without
// waiting for it to exit. Caller is responsible for reaping it (has_exited)
// and stopping it (terminate) when done. Returns -1 on fork failure.
inline pid_t spawn_detached(DltContext &ctx, const std::string &path, const std::vector<std::string> &args) {
    std::vector<std::string> full_args;
    full_args.reserve(args.size() + 1);
    full_args.push_back(path);
    full_args.insert(full_args.end(), args.begin(), args.end());

    DLT_LOG(ctx, DLT_LOG_INFO, DLT_STRING("Spawning:"), DLT_STRING(join_args(full_args).c_str()));

    std::vector<char *> argv;
    argv.reserve(full_args.size() + 1);
    for (const auto &a : full_args) {
        argv.push_back(const_cast<char *>(a.c_str()));
    }
    argv.push_back(nullptr);

    const pid_t pid = fork();
    if (pid < 0) {
        DLT_LOG(ctx, DLT_LOG_ERROR, DLT_STRING("fork() failed:"), DLT_STRING(strerror(errno)));
        return -1;
    }
    if (pid == 0) {
        execvp(argv[0], argv.data());
        _exit(127);
    }
    return pid;
}

// Non-blocking reap: returns true if `pid` has already exited (and consumes
// its zombie), false if it's still running.
inline bool has_exited(pid_t pid) {
    int status = 0;
    const pid_t rc = waitpid(pid, &status, WNOHANG);
    return rc == pid || (rc < 0 && errno == ECHILD);
}

// Stops a process started with spawn_detached: SIGTERM, then a bounded wait,
// escalating to SIGKILL if it hasn't exited in time. Always reaps the child.
inline void terminate(DltContext &ctx, const std::string &name, pid_t pid, int timeout_ms = 2000) {
    DLT_LOG(ctx, DLT_LOG_INFO, DLT_STRING("Stopping process:"), DLT_STRING(name.c_str()), DLT_INT(pid));
    kill(pid, SIGTERM);

    const int poll_ms = 100;
    for (int waited_ms = 0; waited_ms < timeout_ms; waited_ms += poll_ms) {
        if (has_exited(pid)) {
            return;
        }
        usleep(static_cast<useconds_t>(poll_ms) * 1000);
    }

    DLT_LOG(ctx, DLT_LOG_WARN, DLT_STRING("Process did not exit after SIGTERM, sending SIGKILL:"), DLT_STRING(name.c_str()));
    kill(pid, SIGKILL);
    int status = 0;
    waitpid(pid, &status, 0);
}

}  // namespace sm_process
