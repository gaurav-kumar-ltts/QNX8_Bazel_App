load("@rules_cc//cc:defs.bzl", "cc_binary")

# Tool Binary
cc_binary(
    name = "arxml_to_vsomeip",
    srcs = [
        "arxml_to_vsomeip.cpp",
        "someip_config.hpp",
    ],
    defines = [
        'SOMEIP_ARXML_DEFAULT_PATH=\\"config/someip.arxml\\"',
        'SOMEIP_VSOMEIP_DEFAULT_OUTPUT=\\"config/vsomeip.json\\"',
    ],
    deps = [
        "@em_external//:json_headers",
    ],
)

# Client Binary
cc_binary(
    name = "client",
    srcs = [
        "client.cpp",
        "someip_config.hpp",
    ],
    includes = ["lib/vsomeip/interface"],
    features = ["-no_rpath"],
    linkopts = [
        "-ldlt",
        "-lvsomeip3",
        "-lboost_thread",
        "-lboost_system",
        "-lboost_filesystem",
    ],
    deps = [
        "@dlt_external//:dlt_headers",
        "@common_external//:common_headers",
    ],
)

# Server Binary
cc_binary(
    name = "server",
    srcs = [
        "server.cpp",
        "someip_config.hpp",
    ],
    includes = ["lib/vsomeip/interface"],
    features = ["-no_rpath"],
    linkopts = [
        "-ldlt",
        "-lvsomeip3",
        "-lboost_thread",
        "-lboost_system",
        "-lboost_filesystem",
    ],
    deps = [
        "@dlt_external//:dlt_headers",
        "@common_external//:common_headers",
    ],
)