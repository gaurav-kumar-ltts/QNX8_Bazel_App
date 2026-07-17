genrule(
    name = "my_qnx_app_build",
    srcs = ["main.cpp"],
    outs = ["my_qnx_app"],
    cmd = """
    /home/prathik/qnx800/host/linux/x86_64/usr/bin/qcc \
    -Vgcc_ntoaarch64le \
    -g \
    -std=c++14 \
    -I/home/prathik/qnx800/target/qnx/usr/include \
    -o $(location my_qnx_app) \
    $(location main.cpp)
    """,
    visibility = ["//visibility:public"],
)
