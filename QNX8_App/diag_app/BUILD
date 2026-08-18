load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "diag_manager",
    srcs = [
        "diag_main.cpp",
    ],
    copts = [
        "-std=c++17",
        "-lang-c++",
        "-D_GNU_SOURCE",
        "-D_XOPEN_SOURCE=600",
        "-include",
        "cstdlib",
    ],
    linkopts = [
        "-lsocket",
        "-ldlt",
        "-L/home/prathik/qnx800/QNX8_App/dlt-daemon/build/src/lib",
        "-lc++",
        "-lm",
    ],
    deps = [
        "@dlt_includes//:dlt_headers",
    ],
)