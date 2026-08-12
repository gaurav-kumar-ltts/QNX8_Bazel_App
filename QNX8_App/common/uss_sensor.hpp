#pragma once

#include <chrono>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>

namespace uss_sensor {

inline constexpr const char *kHandshakeFlagPath = "/tmp/someip_handshake.ok";
inline constexpr const char *kLatestEchoMmPath = "/tmp/uss_echo_mm.txt";

inline bool write_text_file(const std::string &path, const std::string &content) {
    std::ofstream out(path, std::ios::trunc);
    if (!out.is_open()) {
        return false;
    }
    out << content;
    return static_cast<bool>(out);
}

inline bool write_uint32_file(const std::string &path, std::uint32_t value) {
    return write_text_file(path, std::to_string(value));
}

inline bool read_uint32_file(const std::string &path, std::uint32_t &value_out) {
    std::ifstream in(path);
    if (!in.is_open()) {
        return false;
    }
    std::uint64_t value = 0;
    in >> value;
    if (!in.good() && !in.eof()) {
        return false;
    }
    if (value > 0xFFFFFFFFULL) {
        return false;
    }
    value_out = static_cast<std::uint32_t>(value);
    return true;
}

inline bool set_handshake_flag(bool active) {
    if (active) {
        return write_text_file(kHandshakeFlagPath, "1\n");
    }
    std::error_code ec;
    std::filesystem::remove(kHandshakeFlagPath, ec);
    return true;
}

inline bool read_echo_mm_via_gpiozero(std::uint32_t &echo_mm_out) {
    const char *python_bin = std::getenv("USS_PYTHON_BIN");
    if (!python_bin || !*python_bin) {
        python_bin = "python3";
    }

    std::ostringstream cmd;
    cmd << python_bin
        << " -c \"from gpiozero import DistanceSensor; "
        << "from time import sleep; "
        << "s=DistanceSensor(echo=6, trigger=5, max_distance=4); "
        << "sleep(0.06); "
        << "d=s.distance*1000.0; "
        << "print(int(d) if d>0 else 0)\" 2>/dev/null";

    std::unique_ptr<FILE, int (*)(FILE *)> pipe(popen(cmd.str().c_str(), "r"), pclose);
    if (!pipe) {
        return false;
    }

    char buffer[64] = {0};
    if (!fgets(buffer, sizeof(buffer), pipe.get())) {
        return false;
    }

    char *end = nullptr;
    const unsigned long value = std::strtoul(buffer, &end, 10);
    if (end == buffer || value == 0UL || value > 0xFFFFFFFFUL) {
        return false;
    }

    echo_mm_out = static_cast<std::uint32_t>(value);
    return true;
}

class Hcsr04Sysfs {
public:
    Hcsr04Sysfs(int trigger_pin, int echo_pin)
        : trigger_pin_(trigger_pin),
          echo_pin_(echo_pin),
          trigger_value_path_("/sys/class/gpio/gpio" + std::to_string(trigger_pin_) + "/value"),
          echo_value_path_("/sys/class/gpio/gpio" + std::to_string(echo_pin_) + "/value") {}

    bool init() {
        return ensure_gpio(trigger_pin_, "out") && ensure_gpio(echo_pin_, "in");
    }

    // Returns true and sets echo_us_out on success.
    bool sample_echo_us(std::uint32_t &echo_us_out, std::uint32_t timeout_us = 30000U) {
        if (!write_text_file(trigger_value_path_, "0")) {
            return false;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(2));
        if (!write_text_file(trigger_value_path_, "1")) {
            return false;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(10));
        if (!write_text_file(trigger_value_path_, "0")) {
            return false;
        }

        const auto rise_deadline = std::chrono::steady_clock::now() + std::chrono::microseconds(timeout_us);
        while (std::chrono::steady_clock::now() < rise_deadline) {
            int value = -1;
            if (!read_gpio_value(echo_value_path_, value)) {
                return false;
            }
            if (value == 1) {
                break;
            }
        }

        int level = 0;
        if (!read_gpio_value(echo_value_path_, level) || level != 1) {
            return false;
        }

        const auto pulse_start = std::chrono::steady_clock::now();
        const auto fall_deadline = pulse_start + std::chrono::microseconds(timeout_us);
        while (std::chrono::steady_clock::now() < fall_deadline) {
            int value = -1;
            if (!read_gpio_value(echo_value_path_, value)) {
                return false;
            }
            if (value == 0) {
                const auto pulse_end = std::chrono::steady_clock::now();
                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(pulse_end - pulse_start).count();
                if (duration <= 0) {
                    return false;
                }
                echo_us_out = static_cast<std::uint32_t>(duration);
                return true;
            }
        }

        return false;
    }

    static std::uint32_t echo_us_to_mm(std::uint32_t echo_us) {
        // HC-SR04 conversion: distance_cm ~= echo_us / 58.
        return static_cast<std::uint32_t>((echo_us * 10U + 29U) / 58U);
    }

private:
    static bool read_gpio_value(const std::string &path, int &value_out) {
        std::ifstream in(path);
        if (!in.is_open()) {
            return false;
        }
        char c = 0;
        in >> c;
        if (!in.good() && !in.eof()) {
            return false;
        }
        if (c == '0') {
            value_out = 0;
            return true;
        }
        if (c == '1') {
            value_out = 1;
            return true;
        }
        return false;
    }

    static bool ensure_gpio(int pin, const char *direction) {
        const std::string gpio_dir = "/sys/class/gpio/gpio" + std::to_string(pin);
        if (!std::filesystem::exists(gpio_dir)) {
            if (!write_text_file("/sys/class/gpio/export", std::to_string(pin))) {
                return false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
        return write_text_file(gpio_dir + "/direction", direction);
    }

    int trigger_pin_;
    int echo_pin_;
    std::string trigger_value_path_;
    std::string echo_value_path_;
};

}  // namespace uss_sensor
