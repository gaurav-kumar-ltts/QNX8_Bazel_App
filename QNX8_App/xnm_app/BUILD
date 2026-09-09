load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "xnm_app",
    srcs = [
        "xnm_config.hpp",
        "xnm_main.cpp",
    ],
    copts = [
        "-std=c++17",
    ],
    features = ["-no_rpath"],
    linkopts = [
        "-ldlt",
        "-lsocket",
    ],
    deps = [
        "@dlt_external//:dlt_headers",
        "@em_external//:json_headers",
    ],
)
