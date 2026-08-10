#include "someip_config.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using json = nlohmann::json;

static std::string upper_copy(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
        return static_cast<char>(std::toupper(c));
    });
    return value;
}

struct ServiceEntry {
    std::string app_name;
    std::string service_id;
    std::string peer_service_id;
    std::string instance_id;
    std::string major_version;
    std::string minor_version;
    std::string event_id;
    std::string eventgroup_id;
    std::string unicast_ip;
    std::string port_number;
    std::string protocol;
    std::string multicast_ip;
    std::string multicast_port;
    std::string sd_port;
};

static std::vector<ServiceEntry> parse_arxml(const fs::path &path) {
    const std::string content = someip_config::read_text_file(path);
    const auto service_blocks = someip_config::extract_all_blocks(content, "SOMEIP-SERVICE-INTERFACE-DEPLOYMENT");
    const auto mapping_blocks = someip_config::extract_all_blocks(content, "SOMEIP-SERVICE-INSTANCE-TO-MACHINE-MAPPING");
    const auto application_blocks = someip_config::extract_all_blocks(content, "APPLICATION-SOFTWARE-COMPONENT");

    std::vector<ServiceEntry> entries;
    const std::vector<std::string> app_names = {"example_service_app", "example_consumer_app"};

    for (std::size_t index = 0; index < service_blocks.size(); ++index) {
        const auto &service_block = service_blocks[index];
        const auto &mapping_block = mapping_blocks.empty() ? service_block : mapping_blocks[std::min(index, mapping_blocks.size() - 1U)];

        ServiceEntry entry;
        entry.app_name = index < app_names.size() ? app_names[index] : ("someip_app_" + std::to_string(index));
        entry.service_id = someip_config::to_hex4(someip_config::find_tag_value(service_block, "SERVICE-INTERFACE-ID"));
        entry.peer_service_id = service_blocks.size() > 1U
            ? someip_config::to_hex4(someip_config::find_tag_value(service_blocks[(index + 1U) % service_blocks.size()], "SERVICE-INTERFACE-ID"))
            : entry.service_id;
        entry.instance_id = someip_config::to_hex4(someip_config::find_tag_value(mapping_block, "INSTANCE-ID"));
        entry.major_version = someip_config::find_tag_value(service_block, "MAJOR-VERSION");
        entry.minor_version = someip_config::find_tag_value(service_block, "MINOR-VERSION");
        entry.unicast_ip = someip_config::find_tag_value(mapping_block, "UNICAST-IP-ADDRESS");
        entry.port_number = someip_config::find_tag_value(mapping_block, "PORT-NUMBER");
        entry.protocol = someip_config::find_tag_value(mapping_block, "PROTOCOL");
        entry.multicast_ip = someip_config::find_tag_value(mapping_block, "MULTICAST-IP-ADDRESS");
        entry.multicast_port = someip_config::find_tag_value(mapping_block, "MULTICAST-PORT-NUMBER");
        entry.sd_port = someip_config::find_tag_value(mapping_block, "SD-PORT-NUMBER");

        const auto event_blocks = someip_config::extract_all_blocks(service_block, "SOMEIP-EVENT-DEPLOYMENT");
        entry.event_id = event_blocks.empty()
            ? "0x8001"
            : someip_config::to_hex4(someip_config::find_tag_value(event_blocks.front(), "EVENT-ID"));

        const auto eventgroup_blocks = someip_config::extract_all_blocks(service_block, "SOMEIP-EVENT-GROUP-DEPLOYMENT");
        entry.eventgroup_id = eventgroup_blocks.empty()
            ? "0x0001"
            : someip_config::to_hex4(someip_config::find_tag_value(eventgroup_blocks.front(), "EVENT-GROUP-ID"));

        entries.push_back(entry);
    }

    if (entries.empty()) {
        throw std::runtime_error("No SOME/IP service deployments found in ARXML");
    }

    return entries;
}

static json build_vsomeip_json(const std::vector<ServiceEntry> &entries) {
    json root;
    const std::string default_unicast = (!entries.empty() && !entries.front().unicast_ip.empty())
        ? entries.front().unicast_ip
        : "127.0.0.1";
    root["unicast"] = default_unicast;
    root["logging"] = {
        {"level", "info"},
        {"console", true}
    };

    json applications = json::array();
    json services = json::array();
    json runtime_services = json::array();

    for (const auto &entry : entries) {
        applications.push_back({
            {"name", entry.app_name},
            {"id", entry.service_id}
        });

        json service_entry = {
            {"service", entry.service_id},
            {"peer_service", entry.peer_service_id},
            {"instance", entry.instance_id},
            {"unicast", entry.unicast_ip.empty() ? default_unicast : entry.unicast_ip},
            {"events", {
                {
                    {"event", entry.event_id},
                    {"eventgroup", entry.eventgroup_id},
                    {"is_field", false},
                    {"is_reliable", false}
                }
            }}
        };

        const int port = entry.port_number.empty() ? 30501 : std::stoi(entry.port_number);
        if (upper_copy(entry.protocol) == "TCP") {
            service_entry["reliable"] = port;
        } else {
            service_entry["unreliable"] = port;
        }

        services.push_back(service_entry);

        runtime_services.push_back({
            {"name", entry.app_name},
            {"service", entry.service_id},
            {"peer_service", entry.peer_service_id},
            {"instance", entry.instance_id},
            {"major", entry.major_version.empty() ? "1" : entry.major_version},
            {"minor", entry.minor_version.empty() ? "0" : entry.minor_version},
            {"events", {
                {
                    {"event", entry.event_id},
                    {"eventgroup", entry.eventgroup_id}
                }
            }}
        });
    }

    root["applications"] = applications;
    root["services"] = services;
    root["runtime-services"] = runtime_services;

    const std::string sd_multicast = (!entries.empty() && !entries.front().multicast_ip.empty())
        ? entries.front().multicast_ip
        : "224.224.224.245";
    const std::string sd_port = (!entries.empty() && !entries.front().sd_port.empty())
        ? entries.front().sd_port
        : "30490";
    root["service-discovery"] = {
        {"enable", "true"},
        {"multicast", sd_multicast},
        {"port", sd_port},
        {"protocol", "udp"}
    };

    return root;
}

int main(int argc, char **argv) {
    const fs::path arxml_path = argc > 1 ? fs::path(argv[1]) : fs::path(SOMEIP_ARXML_DEFAULT_PATH);
    const fs::path output_path = argc > 2 ? fs::path(argv[2]) : fs::path(SOMEIP_VSOMEIP_DEFAULT_OUTPUT);

    try {
        const auto entries = parse_arxml(arxml_path);
        const json root = build_vsomeip_json(entries);

        if (!output_path.parent_path().empty()) {
            fs::create_directories(output_path.parent_path());
        }

        std::ofstream output(output_path);
        if (!output.is_open()) {
            std::cerr << "Unable to open output file: " << output_path << '\n';
            return 1;
        }
        output << root.dump(2) << '\n';

        std::cout << "Generated " << output_path << " from " << arxml_path << '\n';
        for (const auto &entry : entries) {
            std::cout << entry.app_name << " service=" << entry.service_id << " instance=" << entry.instance_id << '\n';
        }
        return 0;
    } catch (const std::exception &ex) {
        std::cerr << "Generator error: " << ex.what() << '\n';
        return 1;
    }
}
