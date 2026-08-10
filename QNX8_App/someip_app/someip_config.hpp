#pragma once

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace someip_config {

struct ServiceConfig {
    std::string name;
    std::uint16_t local_service_id{0};
    std::uint16_t peer_service_id{0};
    std::uint16_t instance_id{1};
    std::uint8_t service_major_version{1};
    std::uint32_t service_minor_version{0};
    std::uint16_t event_id{0};
    std::uint16_t eventgroup_id{1};
};

inline std::string trim_copy(std::string value) {
    auto not_space = [](unsigned char ch) { return !std::isspace(ch); };
    value.erase(value.begin(), std::find_if(value.begin(), value.end(), not_space));
    value.erase(std::find_if(value.rbegin(), value.rend(), not_space).base(), value.end());
    return value;
}

inline std::string to_hex4(const std::string &value) {
    int number = 0;
    try {
        number = std::stoi(value, nullptr, 0);
    } catch (...) {
        number = std::stoi(value, nullptr, 16);
    }

    std::ostringstream out;
    out << "0x" << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << number;
    return out.str();
}

inline std::uint16_t parse_u16(const std::string &value) {
    return static_cast<std::uint16_t>(std::stoi(value, nullptr, 0));
}

inline std::string read_text_file(const std::filesystem::path &path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open file: " + path.string());
    }
    std::ostringstream stream;
    stream << input.rdbuf();
    return stream.str();
}

inline std::string find_tag_value(const std::string &text, const std::string &tag) {
    const std::string open_tag = "<" + tag;
    const std::string close_tag = "</" + tag + ">";
    const std::size_t start = text.find(open_tag);
    if (start == std::string::npos) {
        return {};
    }
    const std::size_t end_open = text.find('>', start);
    if (end_open == std::string::npos) {
        return {};
    }
    const std::size_t end = text.find(close_tag, end_open + 1);
    if (end == std::string::npos) {
        return {};
    }
    return trim_copy(text.substr(end_open + 1, end - end_open - 1));
}

inline std::vector<std::string> extract_all_blocks(const std::string &text, const std::string &tag) {
    std::vector<std::string> blocks;
    const std::string open_tag = "<" + tag;
    const std::string close_tag = "</" + tag + ">";

    std::size_t search_pos = 0;
    while (true) {
        const std::size_t start = text.find(open_tag, search_pos);
        if (start == std::string::npos) {
            break;
        }
        const std::size_t end_open = text.find('>', start);
        if (end_open == std::string::npos) {
            break;
        }
        const std::size_t end = text.find(close_tag, end_open + 1);
        if (end == std::string::npos) {
            break;
        }
        blocks.push_back(text.substr(start, end + close_tag.size() - start));
        search_pos = end + close_tag.size();
    }
    return blocks;
}

inline std::string resolve_config_path() {
    const char *env_config = std::getenv("VSOMEIP_CONFIGURATION");
    if (env_config && *env_config) {
        return env_config;
    }

    const std::vector<std::string> candidates = {
        "/etc/someip_app/vsomeip.json",
        "/usr/local/etc/someip_app/vsomeip.json",
        "./vsomeip.json",
        "./input.arxml"
    };

    for (const auto &candidate : candidates) {
        if (std::filesystem::exists(candidate)) {
            return candidate;
        }
    }

    return {};
}

inline std::size_t find_matching_delimiter(const std::string &text, std::size_t start_pos, char open_char, char close_char) {
    bool in_string = false;
    bool escaped = false;
    int depth = 0;

    for (std::size_t i = start_pos; i < text.size(); ++i) {
        const char c = text[i];
        if (in_string) {
            if (escaped) {
                escaped = false;
                continue;
            }
            if (c == '\\') {
                escaped = true;
                continue;
            }
            if (c == '"') {
                in_string = false;
            }
            continue;
        }

        if (c == '"') {
            in_string = true;
            continue;
        }
        if (c == open_char) {
            ++depth;
            continue;
        }
        if (c == close_char) {
            --depth;
            if (depth == 0) {
                return i;
            }
        }
    }

    return std::string::npos;
}

inline std::string find_json_array_for_key(const std::string &text, const std::string &key) {
    const std::string key_pattern = "\"" + key + "\"";
    const std::size_t key_pos = text.find(key_pattern);
    if (key_pos == std::string::npos) {
        return {};
    }
    const std::size_t open_pos = text.find('[', key_pos);
    if (open_pos == std::string::npos) {
        return {};
    }
    const std::size_t close_pos = find_matching_delimiter(text, open_pos, '[', ']');
    if (close_pos == std::string::npos) {
        return {};
    }
    return text.substr(open_pos, close_pos - open_pos + 1U);
}

inline std::vector<std::string> extract_json_objects(const std::string &array_text) {
    std::vector<std::string> objects;
    std::size_t pos = 0;
    while (true) {
        const std::size_t open_pos = array_text.find('{', pos);
        if (open_pos == std::string::npos) {
            break;
        }
        const std::size_t close_pos = find_matching_delimiter(array_text, open_pos, '{', '}');
        if (close_pos == std::string::npos) {
            break;
        }
        objects.push_back(array_text.substr(open_pos, close_pos - open_pos + 1U));
        pos = close_pos + 1U;
    }
    return objects;
}

inline std::string json_string_value(const std::string &object_text, const std::string &key) {
    const std::regex pattern("\\\"" + key + "\\\"\\s*:\\s*\\\"([^\\\"]+)\\\"");
    std::smatch match;
    if (std::regex_search(object_text, match, pattern) && match.size() > 1U) {
        return match[1].str();
    }
    return {};
}

inline ServiceConfig load_from_json(const std::filesystem::path &path, const std::string &app_name) {
    const std::string content = read_text_file(path);
    const std::string runtime_services_array = find_json_array_for_key(content, "runtime-services");
    if (runtime_services_array.empty()) {
        throw std::runtime_error("No runtime-services found in JSON config");
    }

    const auto service_objects = extract_json_objects(runtime_services_array);
    if (service_objects.empty()) {
        throw std::runtime_error("No runtime-services entries found in JSON config");
    }

    const std::string *selected = nullptr;
    for (const auto &entry : service_objects) {
        if (json_string_value(entry, "name") == app_name) {
            selected = &entry;
            break;
        }
    }
    if (!selected) {
        selected = &service_objects.front();
    }

    ServiceConfig config;
    config.name = json_string_value(*selected, "name");
    if (config.name.empty()) {
        config.name = app_name;
    }

    const std::string service_value = json_string_value(*selected, "service");
    const std::string peer_service_value = json_string_value(*selected, "peer_service");
    const std::string instance_value = json_string_value(*selected, "instance");
    const std::string major_value = json_string_value(*selected, "major");
    const std::string minor_value = json_string_value(*selected, "minor");

    config.local_service_id = parse_u16(service_value.empty() ? "0" : service_value);
    config.peer_service_id = parse_u16(peer_service_value.empty() ? (service_value.empty() ? "0" : service_value) : peer_service_value);
    config.instance_id = parse_u16(instance_value.empty() ? "1" : instance_value);
    config.service_major_version = static_cast<std::uint8_t>(parse_u16(major_value.empty() ? "1" : major_value));
    config.service_minor_version = static_cast<std::uint32_t>(std::stoul(minor_value.empty() ? "0" : minor_value, nullptr, 0));

    const std::string events_array = find_json_array_for_key(*selected, "events");
    const auto event_objects = extract_json_objects(events_array);
    if (!event_objects.empty()) {
        const std::string event_value = json_string_value(event_objects.front(), "event");
        const std::string eventgroup_value = json_string_value(event_objects.front(), "eventgroup");
        config.event_id = parse_u16(event_value.empty() ? "0" : event_value);
        config.eventgroup_id = parse_u16(eventgroup_value.empty() ? "1" : eventgroup_value);
    }

    return config;
}

inline ServiceConfig load_from_arxml(const std::filesystem::path &path, const std::string &app_name) {
    const std::string content = read_text_file(path);
    const auto service_blocks = extract_all_blocks(content, "SOMEIP-SERVICE-INTERFACE-DEPLOYMENT");
    const auto mapping_blocks = extract_all_blocks(content, "SOMEIP-SERVICE-INSTANCE-TO-MACHINE-MAPPING");

    if (service_blocks.empty()) {
        throw std::runtime_error("No SOMEIP service blocks found in ARXML");
    }

    std::size_t index = 0;
    if (app_name.find("consumer") != std::string::npos && service_blocks.size() > 1U) {
        index = 1U;
    }

    const std::string &service_block = service_blocks[std::min(index, service_blocks.size() - 1U)];
    const std::string &mapping_block = mapping_blocks.empty()
        ? service_block
        : mapping_blocks[std::min(index, mapping_blocks.size() - 1U)];

    ServiceConfig config;
    config.name = app_name;
    config.local_service_id = parse_u16(find_tag_value(service_block, "SERVICE-INTERFACE-ID"));
    config.peer_service_id = config.local_service_id;
    config.instance_id = parse_u16(find_tag_value(mapping_block, "INSTANCE-ID"));
    config.service_major_version = static_cast<std::uint8_t>(parse_u16(find_tag_value(service_block, "MAJOR-VERSION").empty() ? "1" : find_tag_value(service_block, "MAJOR-VERSION")));
    config.service_minor_version = static_cast<std::uint32_t>(std::stoul(find_tag_value(service_block, "MINOR-VERSION").empty() ? "0" : find_tag_value(service_block, "MINOR-VERSION"), nullptr, 0));

    const auto event_blocks = extract_all_blocks(service_block, "SOMEIP-EVENT-DEPLOYMENT");
    if (!event_blocks.empty()) {
        config.event_id = parse_u16(find_tag_value(event_blocks.front(), "EVENT-ID"));
    } else {
        config.event_id = 0x8001;
    }

    const auto eventgroup_blocks = extract_all_blocks(service_block, "SOMEIP-EVENT-GROUP-DEPLOYMENT");
    if (!eventgroup_blocks.empty()) {
        config.eventgroup_id = parse_u16(find_tag_value(eventgroup_blocks.front(), "EVENT-GROUP-ID"));
    } else {
        config.eventgroup_id = 1;
    }

    return config;
}

inline ServiceConfig load_service_config(const std::filesystem::path &path, const std::string &app_name) {
    if (path.extension() == ".json") {
        return load_from_json(path, app_name);
    }
    if (path.extension() == ".arxml") {
        return load_from_arxml(path, app_name);
    }

    if (path.filename() == "vsomeip.json") {
        return load_from_json(path, app_name);
    }
    return load_from_arxml(path, app_name);
}

}  // namespace someip_config
