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
#include <mutex>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <future>
#include <unistd.h>
#include <vector>

#include "someip_config.hpp"
#include "uss_sensor.hpp"

DLT_DECLARE_CONTEXT(hello_srv_ctx);

namespace {

constexpr const char *APP_NAME = "example_service_app";

std::atomic<bool> g_stop_requested{false};

constexpr int kDefaultTriggerPin = 5;
constexpr int kDefaultEchoPin = 6;
constexpr std::uint32_t kSensorErrorValueMm = 0xFFFFU;

std::vector<std::uint8_t> echo_payload(std::uint32_t echo_mm) {
    return {
        static_cast<std::uint8_t>((echo_mm >> 24U) & 0xFFU),
        static_cast<std::uint8_t>((echo_mm >> 16U) & 0xFFU),
        static_cast<std::uint8_t>((echo_mm >> 8U) & 0xFFU),
        static_cast<std::uint8_t>(echo_mm & 0xFFU)
    };
}

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

void log_dlt_string(const char *message) {
    DLT_LOG(hello_srv_ctx, DLT_LOG_INFO, DLT_STRING(message));
}

class SomeIpService {
public:
    explicit SomeIpService(someip_config::ServiceConfig config)
                : app_(nullptr),
                    config_(std::move(config)),
                    worker_(),
                    notifier_(),
                    running_(false),
                    registered_(false),
                    sensor_(kDefaultTriggerPin, kDefaultEchoPin),
                    last_echo_mm_(0U) {}

    bool init() {
        DLT_LOG(hello_srv_ctx, DLT_LOG_INFO, DLT_STRING("Using VSOMEIP application name"), DLT_STRING(APP_NAME));
        DLT_LOG(hello_srv_ctx, DLT_LOG_INFO, DLT_STRING("Configured service"), DLT_UINT16(config_.local_service_id), DLT_STRING("instance"), DLT_UINT16(config_.instance_id));

        app_ = vsomeip::runtime::get()->create_application(APP_NAME);
        if (!app_) {
            DLT_LOG(hello_srv_ctx, DLT_LOG_ERROR, DLT_STRING("create_application failed"));
            return false;
        }

        if (!app_->init()) {
            DLT_LOG(hello_srv_ctx, DLT_LOG_ERROR, DLT_STRING("vsomeip init failed"));
            return false;
        }

        // app_->register_state_handler([this](vsomeip::state_type_e state) {
        //     DLT_LOG(hello_srv_ctx, DLT_LOG_INFO, DLT_STRING("State changed"), DLT_UINT8(static_cast<std::uint8_t>(state)));
        //     if (state == vsomeip::state_type_e::ST_REGISTERED) {
        //         std::set<vsomeip::eventgroup_t> groups({config_.eventgroup_id});
        //         DLT_LOG(hello_srv_ctx, DLT_LOG_INFO, DLT_STRING("Offering event"), DLT_UINT16(config_.event_id));
        //         app_->offer_event(config_.local_service_id,
        //                           config_.instance_id,
        //                           config_.event_id,
        //                           groups,
        //                           vsomeip::event_type_e::ET_EVENT,
        //                           std::chrono::milliseconds::zero(),
        //                           false,
        //                           true,
        //                           nullptr,
        //                           vsomeip::reliability_type_e::RT_UNRELIABLE);

        //         // app_->register_subscription_handler(
        //         //     config_.local_service_id,
        //         //     config_.instance_id,
        //         //     config_.eventgroup_id,
        //         //     [this](vsomeip::client_t client, const vsomeip_sec_client_t *, const std::string &, bool subscribed) {
        //         //         DLT_LOG(hello_srv_ctx, DLT_LOG_INFO,
        //         //                 DLT_STRING(subscribed ? "Subscription accepted" : "Subscription removed"),
        //         //                 DLT_UINT16(client));
        //         //         if (subscribed) {
        //         //             {
        //         //                 std::lock_guard<std::mutex> lock(subscribers_mutex_);
        //         //                 subscribed_clients_.insert(client);
        //         //             }
        //         //             update_handshake_file();
        //         //             std::uint32_t echo_mm = 0;
        //         //             if (try_read_echo_mm(echo_mm)) {
        //         //                 notify_echo_mm(echo_mm);
        //         //             } else {
        //         //                 DLT_LOG(hello_srv_ctx, DLT_LOG_WARN,
        //         //                         DLT_STRING("Subscription ACK sent but no valid USS echo yet"));
        //         //             }
        //         //         } else {
        //         //             {
        //         //                 std::lock_guard<std::mutex> lock(subscribers_mutex_);
        //         //                 subscribed_clients_.erase(client);
        //         //             }
        //         //             update_handshake_file();
        //         //         }
        //         //         return true;
        //         //     });

        //         DLT_LOG(hello_srv_ctx, DLT_LOG_INFO,
        //             DLT_STRING("Offering service"),
        //             DLT_UINT16(config_.local_service_id),
        //             DLT_STRING("instance"),
        //             DLT_UINT16(config_.instance_id),
        //             DLT_STRING("major"),
        //                 DLT_UINT8(config_.service_major_version),
        //             DLT_STRING("minor"),
        //                 DLT_UINT32(config_.service_minor_version));
        //         app_->offer_service(config_.local_service_id,
        //                     config_.instance_id,
        //                     config_.service_major_version,
        //                     config_.service_minor_version);
        //         registered_.store(true);
        //     } else {
        //         registered_.store(false);
        //     }
        // });

        DLT_LOG(hello_srv_ctx, DLT_LOG_INFO, DLT_STRING("Service initialized successfully"));
        if (!sensor_.init()) {
            DLT_LOG(hello_srv_ctx, DLT_LOG_WARN,
                    DLT_STRING("USS sensor GPIO init failed; check permissions and wiring"),
                    DLT_STRING("trigger"), DLT_INT32(kDefaultTriggerPin),
                    DLT_STRING("echo"), DLT_INT32(kDefaultEchoPin));
        }
        return true;
    }

    void start() {
        if (running_.exchange(true)) {
            return;
        }
        worker_ = std::thread([this]() {
            DLT_LOG(hello_srv_ctx, DLT_LOG_INFO, DLT_STRING("Starting vsomeip application"));
            app_->start();
        });

        notifier_ = std::thread([this]() {
            std::uint32_t missed_samples = 0;
            while (running_.load()) {
                if (registered_.load() && has_active_subscribers()) {
                    std::uint32_t echo_mm = 0;
                    if (try_read_echo_mm(echo_mm)) {
                        missed_samples = 0;
                        notify_echo_mm(echo_mm);
                    } else {
                        ++missed_samples;
                        if (missed_samples % 20U == 0U) {
                            DLT_LOG(hello_srv_ctx, DLT_LOG_WARN,
                                    DLT_STRING("No valid USS echo sample yet; skipping notify"));
                        }
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
    }

    void stop() {
        if (!running_.load()) {
            return;
        }
        running_.store(false);
        registered_.store(false);
        {
            std::lock_guard<std::mutex> lock(subscribers_mutex_);
            subscribed_clients_.clear();
        }
        update_handshake_file();

        if (notifier_.joinable()) {
            notifier_.join();
        }

        DLT_LOG(hello_srv_ctx, DLT_LOG_INFO, DLT_STRING("Stopping vsomeip application"));
        app_->stop_offer_event(config_.local_service_id, config_.instance_id, config_.event_id);
        app_->stop_offer_service(config_.local_service_id, config_.instance_id);
        app_->stop();
        if (worker_.joinable()) {
            worker_.join();
        }
    }

    bool is_registered() const {
        return registered_.load();
    }

    void notify_echo_mm(std::uint32_t echo_mm) {
        if (!running_ || !registered_.load()) {
            return;
        }
        auto payload = vsomeip::runtime::get()->create_payload();
        auto bytes = echo_payload(echo_mm);
        payload->set_data(bytes);
        // Force notify so repeated distance values are still propagated.
        app_->notify(config_.local_service_id, config_.instance_id, config_.event_id, payload, true);
        DLT_LOG(hello_srv_ctx, DLT_LOG_INFO,
                DLT_STRING("Notified USS echo"),
            DLT_STRING("mm"), DLT_UINT32(echo_mm));
    }

    ~SomeIpService() {
        stop();
    }

private:
    bool try_read_echo_mm(std::uint32_t &echo_mm_out) {
        // Retry a few times to avoid publishing stale/zero data immediately after SUBACK.
        for (int attempt = 0; attempt < 5; ++attempt) {
            std::uint32_t echo_us = 0;
            if (sensor_.sample_echo_us(echo_us)) {
                const std::uint32_t echo_mm = uss_sensor::Hcsr04Sysfs::echo_us_to_mm(echo_us);
                if (echo_mm > 0U) {
                    last_echo_mm_.store(echo_mm);
                    if (!uss_sensor::write_uint32_file(uss_sensor::kLatestEchoMmPath, echo_mm)) {
                        DLT_LOG(hello_srv_ctx, DLT_LOG_WARN,
                                DLT_STRING("Failed to write latest USS value file"),
                                DLT_STRING(uss_sensor::kLatestEchoMmPath));
                    }
                    echo_mm_out = echo_mm;
                    return true;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

        std::uint32_t gpiozero_mm = 0;
        if (uss_sensor::read_echo_mm_via_gpiozero(gpiozero_mm)) {
            last_echo_mm_.store(gpiozero_mm);
            if (!uss_sensor::write_uint32_file(uss_sensor::kLatestEchoMmPath, gpiozero_mm)) {
                DLT_LOG(hello_srv_ctx, DLT_LOG_WARN,
                        DLT_STRING("Failed to write latest USS value file"),
                        DLT_STRING(uss_sensor::kLatestEchoMmPath));
            }
            DLT_LOG(hello_srv_ctx, DLT_LOG_INFO,
                    DLT_STRING("USS read via gpiozero fallback"),
                    DLT_STRING("mm"), DLT_UINT32(gpiozero_mm));
            echo_mm_out = gpiozero_mm;
            return true;
        }

        std::uint32_t file_echo = 0;
        if (uss_sensor::read_uint32_file(uss_sensor::kLatestEchoMmPath, file_echo) && file_echo > 0U) {
            last_echo_mm_.store(file_echo);
            echo_mm_out = file_echo;
            return true;
        }

        const std::uint32_t last_echo = last_echo_mm_.load();
        if (last_echo > 0U) {
            echo_mm_out = last_echo;
            return true;
        }

        // Explicit sensor error signaling: send 0xFFFF when no valid echo value is available.
        echo_mm_out = kSensorErrorValueMm;
        last_echo_mm_.store(kSensorErrorValueMm);
        if (!uss_sensor::write_uint32_file(uss_sensor::kLatestEchoMmPath, kSensorErrorValueMm)) {
            DLT_LOG(hello_srv_ctx, DLT_LOG_WARN,
                    DLT_STRING("Failed to write USS sensor error value file"),
                    DLT_STRING(uss_sensor::kLatestEchoMmPath));
        }
        DLT_LOG(hello_srv_ctx, DLT_LOG_WARN,
                DLT_STRING("USS read failed; publishing sensor error value"),
            DLT_STRING("mm"), DLT_UINT32(kSensorErrorValueMm));
        return true;
    }

    void update_handshake_file() {
        const bool active = has_active_subscribers();
        if (!uss_sensor::set_handshake_flag(active)) {
            DLT_LOG(hello_srv_ctx, DLT_LOG_WARN,
                    DLT_STRING("Failed to update handshake flag"),
                    DLT_STRING(uss_sensor::kHandshakeFlagPath));
        }
    }

    bool has_active_subscribers() const {
        std::lock_guard<std::mutex> lock(subscribers_mutex_);
        return !subscribed_clients_.empty();
    }

    std::shared_ptr<vsomeip::application> app_;
    someip_config::ServiceConfig config_;
    std::thread worker_;
    std::thread notifier_;
    std::atomic<bool> running_;
    std::atomic<bool> registered_;
    uss_sensor::Hcsr04Sysfs sensor_;
    std::atomic<std::uint32_t> last_echo_mm_;
    mutable std::mutex subscribers_mutex_;
    std::set<vsomeip::client_t> subscribed_clients_;
};

}  // namespace

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
void cleanup(int signal_number) {
    if (signal_number == SIGINT || signal_number == SIGTERM) {
        std::_Exit(128 + signal_number);
    }
}
#endif

int main() {
    DLT_REGISTER_APP("HSRV", "Hello Server");
    DLT_REGISTER_CONTEXT(hello_srv_ctx, "HSCT", "Hello Server Context");

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    std::signal(SIGINT, cleanup);
    std::signal(SIGTERM, cleanup);
#endif

    DLT_LOG(hello_srv_ctx, DLT_LOG_INFO, DLT_STRING("Initializing SOME/IP DLT service"));

    const auto config_path = resolve_config_path();
    if (config_path.empty()) {
        DLT_LOG(hello_srv_ctx, DLT_LOG_ERROR, DLT_STRING("No VSOMEIP configuration found"));
        DLT_UNREGISTER_CONTEXT(hello_srv_ctx);
        DLT_UNREGISTER_APP();
        return 1;
    }

    setenv("VSOMEIP_CONFIGURATION", config_path.c_str(), 1);
    setenv("VSOMEIP_APPLICATION_NAME", APP_NAME, 1);

    const auto service_config = someip_config::load_service_config(config_path, APP_NAME);
    SomeIpService service(service_config);

    if (!service.init()) {
        DLT_LOG(hello_srv_ctx, DLT_LOG_ERROR, DLT_STRING("Service initialization failed"));
        DLT_UNREGISTER_CONTEXT(hello_srv_ctx);
        DLT_UNREGISTER_APP();
        return 1;
    }

    service.start();
    DLT_LOG(hello_srv_ctx, DLT_LOG_INFO, DLT_STRING("Service started"));

    while (!g_stop_requested.load()) {
        if (getppid() == 1) {
            DLT_LOG(hello_srv_ctx, DLT_LOG_WARN, DLT_STRING("Parent process lost, forcing exit"));
            std::_Exit(125);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    auto stop_future = std::async(std::launch::async, [&service]() {
        service.stop();
    });

    if (stop_future.wait_for(std::chrono::seconds(10)) != std::future_status::ready) {
        DLT_LOG(hello_srv_ctx, DLT_LOG_ERROR, DLT_STRING("SOME/IP shutdown timed out after 10s, forcing exit"));
        std::_Exit(124);
    }

    DLT_LOG(hello_srv_ctx, DLT_LOG_INFO, DLT_STRING("Service stopped"));
    DLT_UNREGISTER_CONTEXT(hello_srv_ctx);
    DLT_UNREGISTER_APP();
    return 0;
}
