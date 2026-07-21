# Diag Daemon
add_executable(diagd main.cpp)

target_include_directories(diagd PRIVATE
    ${DLT_INCLUDE_DIR}
)

target_link_libraries(diagd
    dlt
    Threads::Threads
)
