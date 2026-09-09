load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "ecdsa",
    srcs = [
        "ecdsa.c",
    ],
    copts = [
        "-std=c++17",
    ],
    features = ["-no_rpath"],
    linkopts = [
        "-lssl",
        "-lcrypto",
    ],
)
