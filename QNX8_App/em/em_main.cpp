#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <unordered_set>
#include <nlohmann/json.hpp>
#include <dlt/dlt.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <chrono>
#include <thread>

namespace fs = std::filesystem;
DLT_DECLARE_CONTEXT(em_ctx);

using json = nlohmann::json;

struct AppInfo {
    std::string name;
    std::string path;
    int priority;
    std::string type;
};

std::vector<AppInfo> loadManifest(const std::string& filepath) {
    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("Loading manifest from"), DLT_STRING(filepath.c_str()));
    std::ifstream f(filepath);
    if (!f.is_open()) {
        DLT_LOG(em_ctx, DLT_LOG_ERROR, DLT_STRING("Cannot open manifest file"), DLT_STRING(filepath.c_str()));
        std::cerr << "Cannot open manifest: " << filepath << std::endl;
        exit(EXIT_FAILURE);
    }

    json j;
    DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("Parsing JSON manifest"));
    try {
        f >> j;
    } catch (const std::exception& e) {
        DLT_LOG(em_ctx, DLT_LOG_ERROR, DLT_STRING("JSON parsing failed"), DLT_STRING(e.what()));
        std::cerr << "JSON parsing failed: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<AppInfo> apps;
    DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("Extracting apps from manifest"));
    for (const auto& app : j["apps_to_start"]) {
        AppInfo appInfo = {
            app["name"].get<std::string>(),
            app["path"].get<std::string>(),
            app["priority"].get<int>(),
            app["type"].get<std::string>()
        };
        DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("Found app in manifest"), 
                DLT_STRING("name"), DLT_STRING(appInfo.name.c_str()),
                DLT_STRING("path"), DLT_STRING(appInfo.path.c_str()),
                DLT_STRING("priority"), DLT_INT(appInfo.priority),
                DLT_STRING("type"), DLT_STRING(appInfo.type.c_str()));
        apps.push_back(appInfo);
    }

    DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("Sorting apps by priority"));
    std::sort(apps.begin(), apps.end(), [](const AppInfo& a, const AppInfo& b) {
        return a.priority < b.priority;
    });

    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("Loaded"), DLT_UINT(apps.size()), DLT_STRING("apps from manifest"));
    return apps;
}

std::unordered_set<std::string> listExecutablesIn(const std::string& dir) {
    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("Listing executables in directory"), DLT_STRING(dir.c_str()));
    std::unordered_set<std::string> executables;
    try {
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (fs::is_regular_file(entry)) {
                std::string path = entry.path().string();
                DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("Checking file"), DLT_STRING(path.c_str()));
                if (access(path.c_str(), X_OK) == 0) {
                    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("Found executable"), DLT_STRING(path.c_str()));
                    executables.insert(path);
                } else {
                    DLT_LOG(em_ctx, DLT_LOG_WARN, DLT_STRING("File not executable"), DLT_STRING(path.c_str()), 
                            DLT_STRING("error"), DLT_STRING(strerror(errno)));
                }
            }
        }
    } catch (const std::exception& e) {
        DLT_LOG(em_ctx, DLT_LOG_ERROR, DLT_STRING("Error listing directory"), DLT_STRING(dir.c_str()), 
                DLT_STRING("error"), DLT_STRING(e.what()));
    }
    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("Found"), DLT_UINT(executables.size()), DLT_STRING("executables in"), DLT_STRING(dir.c_str()));
    return executables;
}

void waitForFifo(const std::string& fifoPath, int timeoutSeconds = 10) {
    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("Waiting for FIFO"), DLT_STRING(fifoPath.c_str()), 
            DLT_STRING("timeout"), DLT_INT(timeoutSeconds), DLT_STRING("seconds"));
    int waited = 0;
    while (access(fifoPath.c_str(), W_OK) != 0) {
        if (waited >= timeoutSeconds) {
            DLT_LOG(em_ctx, DLT_LOG_ERROR, DLT_STRING("Timeout waiting for FIFO"), DLT_STRING(fifoPath.c_str()));
            std::cerr << "Timeout waiting for FIFO: " << fifoPath << std::endl;
            exit(EXIT_FAILURE);
        }
        DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("FIFO not ready, waiting"), DLT_INT(waited + 1), DLT_STRING("seconds"));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        waited++;
    }
    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("FIFO is ready"), DLT_STRING(fifoPath.c_str()));
}

void launchApp(const AppInfo& app, std::vector<pid_t>& nonDaemonPids) {
    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("Attempting to launch app"), DLT_STRING(app.name.c_str()), 
            DLT_STRING("path"), DLT_STRING(app.path.c_str()));
    pid_t pid = fork();
    if (pid == 0) {
        DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("In child process, setting LD_LIBRARY_PATH"));
        setenv("LD_LIBRARY_PATH", "/usr/local/lib", 1);
        DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("Executing app"), DLT_STRING(app.path.c_str()));
        execl(app.path.c_str(), app.path.c_str(), nullptr);
        DLT_LOG(em_ctx, DLT_LOG_ERROR, DLT_STRING("execl failed for"), DLT_STRING(app.path.c_str()), 
                DLT_STRING("error"), DLT_STRING(strerror(errno)));
        _exit(EXIT_FAILURE);
    } else if (pid > 0) {
        DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("Started app"), DLT_STRING(app.name.c_str()), 
                DLT_STRING("PID"), DLT_INT(pid));
        if (app.type != "daemon") {
            DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("Tracking non-daemon app"), DLT_STRING(app.name.c_str()), 
                    DLT_STRING("PID"), DLT_INT(pid));
            nonDaemonPids.push_back(pid);
        }
    } else {
        DLT_LOG(em_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to fork for app"), DLT_STRING(app.name.c_str()), 
                DLT_STRING("error"), DLT_STRING(strerror(errno)));
    }
}

int main() {
    DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("Setting DLT environment variables"));
    setenv("DLT_PIPE_DIR", "/tmp", 1);
    setenv("DLT_FORCE_QUIT", "1", 1);

    DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("Waiting for DLT FIFO"));
    waitForFifo("/tmp/dlt");

    DLT_REGISTER_APP("EM", "Execution Manager");
    DLT_REGISTER_CONTEXT(em_ctx, "EMCT", "EM Context");
    DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("Enabling local print for testing"));
    DLT_ENABLE_LOCAL_PRINT();
    
    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("Execution Manager starting"));
    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("[TIMING] Application Starting..."));

    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("EM startup complete, listing executables"));
    const auto executables = listExecutablesIn("/usr/local/bin");
    DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("Loading manifest"));
    const auto apps = loadManifest("/etc/em/manifest.json");

    std::vector<pid_t> nonDaemonPids;
    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("Processing"), DLT_UINT(apps.size()), DLT_STRING("apps from manifest"));
    for (const auto& app : apps) {
        DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("Checking if app path exists in executables"), 
                DLT_STRING(app.path.c_str()));
        if (executables.count(app.path)) {
            DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("App path found, launching"), DLT_STRING(app.name.c_str()));
            launchApp(app, nonDaemonPids);
        } else {
            DLT_LOG(em_ctx, DLT_LOG_WARN, DLT_STRING("Skipping app"), DLT_STRING(app.name.c_str()), 
                    DLT_STRING("path not found or not executable"), DLT_STRING(app.path.c_str()));
        }
    }

    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("All apps launched. EM entering monitoring loop."));
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        // Future: Check child pids, restart if needed.
        DLT_LOG(em_ctx, DLT_LOG_DEBUG, DLT_STRING("EM heartbeat..."));
    }

    DLT_LOG(em_ctx, DLT_LOG_INFO, DLT_STRING("Execution Manager exiting"));
    return EXIT_SUCCESS;
}
