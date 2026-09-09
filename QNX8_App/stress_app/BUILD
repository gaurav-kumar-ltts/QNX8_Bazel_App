load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "stress_app",
    srcs = [
        "stress_main.cpp",
    ],
    copts = [
        "-std=c++17",
    ],
    features = ["-no_rpath"],
)
