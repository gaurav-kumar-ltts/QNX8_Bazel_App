# MSM (Machine State Manager)
add_executable(machine_sm sm_main.cc)

target_include_directories(machine_sm PRIVATE
    ${DLT_INCLUDE_DIR}
)

target_link_libraries(machine_sm
    dlt
    Threads::Threads
    rt  # For shared memory (shm_open)
)
