load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "diagd",
    srcs = ["daigd_main.cpp"],
    copts = [
        "-std=c++17",
        "-lang-c++",
        "-Idlt_include",
        "-Idlt_include/dlt",
        "-Idlt_build_include",
        "-Idlt_build_include/dlt",
    ],
    linkopts = [
        "-lsocket",
        "-ldlt",
        "-Ldlt_libs",
    ],
)

