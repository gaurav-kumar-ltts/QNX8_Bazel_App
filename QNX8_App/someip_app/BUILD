load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

# Define a local library containing all DLT headers (source + generated)
cc_library(
    name = "dlt_deps",
    hdrs = glob([
        "dlt-daemon/include/**/*.h",
        "dlt_build_include/**/*.h",
    ]),
    includes = [
        "dlt-daemon/include",
        "dlt_build_include",
        "dlt_build_include/dlt",
    ],
)

cc_binary(
    name = "arxml_to_vsomeip",
    srcs = [
        "arxml_to_vsomeip.cpp",
        "someip_config.hpp",
    ],
)

cc_binary(
    name = "client",
    srcs = [
        "client.cpp",
        "someip_config.hpp",
    ],
    deps = [
        ":dlt_deps",
    ],
)

cc_binary(
    name = "server",
    srcs = [
        "server.cpp",
        "someip_config.hpp",
    ],
    deps = [
        ":dlt_deps",
    ],
)