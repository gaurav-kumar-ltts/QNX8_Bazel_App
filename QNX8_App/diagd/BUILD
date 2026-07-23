load("@rules_cc//cc:defs.bzl", "cc_binary")

filegroup(
    name = "dlt_headers",
    srcs = glob([
        "dlt_include/**/*.h",
        "dlt_build_include/**/*.h",
    ]),
)

cc_binary(
    name = "diagd",
    srcs = [
        "daigd_main.cpp",
        ":dlt_headers",
    ],
    copts = [
        "-std=c++17",
        "-lang-c++",
        "-Idlt_include",
        "-Idlt_build_include",
        "-Idlt_include/dlt",
        "-Idlt_build_include/dlt",
    ],
    linkopts = [
        "-lsocket",
        "-ldlt",
        "-L/home/prathik/qnx800/QNX8_App/dlt-daemon/build/src/lib",
        # Force the linkage of the QNX standard C++ library and math properties
        "-lc++",
        "-lm",
    ],
)
