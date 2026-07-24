# QNX8_Bazel_App

his project builds C++ binaries for **QNX 8.0 AArch64** using Bazel.

---

## Single-Step Complete Project Setup & Build

Run this single command in your project root directory (e.g., `~/qnx800/QNX8_App/machine_sm`) to generate all configuration files (`MODULE.bazel`, `BUILD.bazel`, `.bazelrc`), establish local workspace symlinks, and run the Bazel build:

```bash
# 1. Symlink external DLT library into workspace root
ln -snf /home/prathik/qnx800/QNX8_App/dlt-daemon dlt-daemon

# 2. Generate MODULE.bazel
cat << 'MODULE_EOF' > MODULE.bazel
module(
    name = "machine_sm_project",
    version = "1.0",
)
bazel_dep(name = "rules_cc", version = "0.2.17")
MODULE_EOF

# 3. Generate BUILD.bazel
cat << 'BUILD_EOF' > BUILD.bazel
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "dlt_lib",
    hdrs = glob([
        "dlt-daemon/include/**/*.h",
        "dlt-daemon/build/include/**/*.h",
    ]),
    includes = [
        "dlt-daemon/include",
        "dlt-daemon/include/dlt",
        "dlt-daemon/build/include",
        "dlt-daemon/build/include/dlt",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "state_manager",
    srcs = ["sm_main.cc"],
    copts = ["-std=c++17"],
    linkopts = [
        "-lsocket",
        "-ldlt",
        "-L/home/prathik/qnx800/QNX8_App/dlt-daemon/build/src/lib",
        "-lc++",
        "-lm",
    ],
    deps = [":dlt_lib"],
)
BUILD_EOF

# 4. Generate .bazelrc configuration
cat << 'RC_EOF' > .bazelrc
build:qnx_aarch64 --repo_env=CC=/home/prathik/qnx800/QNX8_App/diagd/qcc_wrapper.sh
build:qnx_aarch64 --action_env=CC=/home/prathik/qnx800/QNX8_App/diagd/qcc_wrapper.sh
build:qnx_aarch64 --action_env=CXX=/home/prathik/qnx800/QNX8_App/diagd/qcc_wrapper.sh
build:qnx_aarch64 --action_env=BAZEL_COMPILER=qcc
build:qnx_aarch64 --copt=-Vgcc_ntoaarch64le
build:qnx_aarch64 --linkopt=-Vgcc_ntoaarch64le
build:qnx_aarch64 --copt=-D_XOPEN_SOURCE=600
build:qnx_aarch64 --incompatible_strict_action_env
build:qnx_aarch64 --action_env=QNX_HOST=/home/prathik/qnx800/host/linux/x86_64
build:qnx_aarch64 --action_env=QNX_TARGET=/home/prathik/qnx800/target/qnx
build:qnx_aarch64 --action_env=HOME=/home/prathik
build:qnx_aarch64 --action_env=USER=prathik
build:qnx_aarch64 --sandbox_add_mount_pair=/home/prathik/.qnx
build:qnx_aarch64 --sandbox_writable_path=/home/prathik/.qnx
build:qnx_aarch64 --jobs=1
RC_EOF

# 5. Clean & Build Target Binary
bazel clean --expunge
bazel build --config=qnx_aarch64 //:state_manager
