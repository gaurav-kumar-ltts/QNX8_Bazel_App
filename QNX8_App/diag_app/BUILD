genrule(
    name = "my_daig_app",
    srcs = ["diag_main.cpp"],
    outs = ["diag_app_bin"],
    cmd = """
    /home/prathik/qnx800/host/linux/x86_64/usr/bin/qcc \
    -Vgcc_ntoaarch64le \
    -g \
    -std=c++11 \
    -I/home/prathik/qnx800/target/qnx/usr/include \
    -D"DLT_DECLARE_CONTEXT(x)=" \
    -D"DLT_REGISTER_APP(x,y)=" \
    -D"DLT_REGISTER_CONTEXT(x,y,z)=" \
    -D"DLT_UNREGISTER_CONTEXT(x)=" \
    -D"DLT_UNREGISTER_APP()=" \
    -D"DLT_ENABLE_LOCAL_PRINT()=" \
    -D"DLT_LOG(ctx,level,...)=std::cout << __LINE__ << " \
    -D"DLT_LOG_INFO=0" -D"DLT_LOG_DEBUG=0" -D"DLT_LOG_ERROR=0" -D"DLT_LOG_WARN=0" \
    -D"DLT_STRING(x)=x" -D"DLT_UINT8(x)=(int)x" -D"DLT_UINT16(x)=(int)x" -D"DLT_UINT(x)=(int)x" -D"DLT_INT(x)=x" \
    -o $(location diag_app_bin) \
    $(location diag_main.cpp)
    """,
    visibility = ["//visibility:public"],
)
