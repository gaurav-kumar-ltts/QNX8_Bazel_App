#include <vsomeip/vsomeip.hpp>
#include <dlt/dlt.h>

#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <set>
#include <vector>

#include <unistd.h>

#include "someip_config.hpp"

DLT_DECLARE_CONTEXT(cli_ctx);

namespace {

constexpr const char *APP_NAME = "example_consumer_app";
constexpr const char *PAYLOAD_FILE = "/tmp/someip_received_payload.bin";

std::atomic<bool> g_stop_requested{false};

std::string resolve_config_path() {
    const char *env_config = std::getenv("VSOMEIP_CONFIGURATION");
    if (env_config && *env_config) {
        return env_config;
    }

    const std::vector<std::string> candidates = {
        "/etc/someip_app/vsomeip.json",
        "/usr/local/etc/someip_app/vsomeip.json",
        "./vsomeip.json"
    };

    for (const auto &candidate : candidates) {
        if (std::filesystem::exists(candidate)) {
            return candidate;
        }
    }

    return {};
}

void save_payload(const std::shared_ptr<vsomeip::payload> &payload) {
    if (!payload) {
        return;
    }

    const auto *data = payload->get_data();
    const auto length = payload->get_length();
    if (!data || length == 0U) {
        return;
    }

    std::ofstream output(PAYLOAD_FILE, std::ios::binary | std::ios::trunc);
    if (!output.is_open()) {
        DLT_LOG(cli_ctx, DLT_LOG_ERROR, DLT_STRING("Failed to open payload file"), DLT_STRING(PAYLOAD_FILE));
        return;
    }

    output.write(reinterpret_cast<const char *>(data), static_cast<std::streamsize>(length));
    DLT_LOG(cli_ctx, DLT_LOG_INFO, DLT_STRING("Saved payload to"), DLT_STRING(PAYLOAD_FILE), DLT_STRING("length"), DLT_UINT32(static_cast<std::uint32_t>(length)));
}

class SomeIpConsumer {
public:
    explicit SomeIpConsumer(someip_config::ServiceConfig config)
        : app_(nullptr), config_(std::move(config)), running_(false), subscribed_(false) {}

    bool init() {
        const std::string config_path = resolve_config_path();
        if (config_path.empty()) {
            DLT_LOG(cli_ctx, DLT_LOG_ERROR, DLT_STRING("No VSOMEIP configuration found"));
            return false;
        }

        setenv("VSOMEIP_CONFIGURATION", config_path.c_str(), 1);
        setenv("VSOMEIP_APPLICATION_NAME", APP_NAME, 1);

        DLT_LOG(cli_ctx, DLT_LOG_INFO, DLT_STRING("Using VSOMEIP configuration"), DLT_STRING(config_path.c_str()));
        DLT_LOG(cli_ctx, DLT_LOG_INFO, DLT_STRING("Using VSOMEIP application name"), DLT_STRING(APP_NAME));

        app_ = vsomeip::runtime::get()->create_application(APP_NAME);
        if (!app_) {
            DLT_LOG(cli_ctx, DLT_LOG_ERROR, DLT_STRING("create_application failed"));
            return false;
        }

        if (!app_->init()) {
            DLT_LOG(cli_ctx, DLT_LOG_ERROR, DLT_STRING("vsomeip init failed"));
            return false;
        }

        app_->register_message_handler(
            config_.peer_service_id,
            config_.instance_id,
            config_.event_id,
            [this](const std::shared_ptr<vsomeip::message> &message) {
                if (!message || !message->get_payload()) {
                    DLT_LOG(cli_ctx, DLT_LOG_WARN, DLT_STRING("Received empty notification"));
                    return;
                }

                save_payload(message->get_payload());
            });

        app_->register_availability_handler(
            config_.peer_service_id,
            config_.instance_id,
            [this](vsomeip::service_t service, vsomeip::instance_t instance, bool available) {
                DLT_LOG(cli_ctx, DLT_LOG_INFO, DLT_STRING("Availability changed"), DLT_UINT16(service), DLT_STRING("instance"), DLT_UINT16(instance), DLT_STRING("available"), DLT_BOOL(available));
                if (!available) {
                    subscribed_.store(false);
                    return;
                }

                if (!subscribed_.load()) {
                    DLT_LOG(cli_ctx, DLT_LOG_INFO, DLT_STRING("Service available, subscribing to eventgroup"));
                    app_->request_event(config_.peer_service_id,
                                        config_.instance_id,
                                        config_.event_id,
                                        std::set<vsomeip::eventgroup_t>{config_.eventgroup_id},
                                        vsomeip::event_type_e::ET_EVENT,
                                        vsomeip::reliability_type_e::RT_UNRELIABLE);
                    app_->subscribe(config_.peer_service_id, config_.instance_id, config_.eventgroup_id);
                    subscribed_.store(true);
                }
            });

        app_->request_service(config_.peer_service_id, config_.instance_id);
        app_->request_event(config_.peer_service_id,
                            config_.instance_id,
                            config_.event_id,
                            std::set<vsomeip::eventgroup_t>{config_.eventgroup_id},
                            vsomeip::event_type_e::ET_EVENT,
                            vsomeip::reliability_type_e::RT_UNRELIABLE);

        DLT_LOG(cli_ctx, DLT_LOG_INFO, DLT_STRING("Consumer initialized successfully"));
        return true;
    }

    void start() {
        if (running_) {
            return;
        }
        running_ = true;
        worker_ = std::thread([this]() {
            DLT_LOG(cli_ctx, DLT_LOG_INFO, DLT_STRING("Starting vsomeip consumer"));
            app_->start();
        });
    }

    void stop() {
        if (!running_) {
            return;
        }

        if (subscribed_.load()) {
            app_->unsubscribe(config_.peer_service_id, config_.instance_id, config_.eventgroup_id);
            subscribed_.store(false);
        }

        app_->stop();
        if (worker_.joinable()) {
            worker_.join();
        }
        running_ = false;
    }

    ~SomeIpConsumer() {
        stop();
    }

private:
    std::shared_ptr<vsomeip::application> app_;
    someip_config::ServiceConfig config_;
    std::thread worker_;
    bool running_;
    std::atomic<bool> subscribed_;
};

}  // namespace

void cleanup(int signal_number) {
    if (signal_number == SIGINT || signal_number == SIGTERM) {
        g_stop_requested.store(true);
    }
}

int main() {
    DLT_REGISTER_APP("HCLI", "Hello Consumer");
    DLT_REGISTER_CONTEXT(cli_ctx, "CLCT", "Consumer Context");

    std::signal(SIGINT, cleanup);
    std::signal(SIGTERM, cleanup);

    DLT_LOG(cli_ctx, DLT_LOG_INFO, DLT_STRING("Initializing SOME/IP consumer"));

    const auto config_path = resolve_config_path();
    if (config_path.empty()) {
        DLT_LOG(cli_ctx, DLT_LOG_ERROR, DLT_STRING("No VSOMEIP configuration found"));
        DLT_UNREGISTER_CONTEXT(cli_ctx);
        DLT_UNREGISTER_APP();
        return 1;
    }

    setenv("VSOMEIP_CONFIGURATION", config_path.c_str(), 1);
    setenv("VSOMEIP_APPLICATION_NAME", APP_NAME, 1);

    const auto consumer_config = someip_config::load_service_config(config_path, APP_NAME);
    SomeIpConsumer consumer(consumer_config);
    if (!consumer.init()) {
        DLT_LOG(cli_ctx, DLT_LOG_ERROR, DLT_STRING("Consumer initialization failed"));
        DLT_UNREGISTER_CONTEXT(cli_ctx);
        DLT_UNREGISTER_APP();
        return 1;
    }

    consumer.start();
    DLT_LOG(cli_ctx, DLT_LOG_INFO, DLT_STRING("Consumer started"));

    while (!g_stop_requested.load()) {
        if (getppid() == 1) {
            DLT_LOG(cli_ctx, DLT_LOG_WARN, DLT_STRING("Parent process lost, forcing exit"));
            std::_Exit(125);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    consumer.stop();
    DLT_LOG(cli_ctx, DLT_LOG_INFO, DLT_STRING("Consumer stopped"));
    DLT_UNREGISTER_CONTEXT(cli_ctx);
    DLT_UNREGISTER_APP();
    return 0;
}
