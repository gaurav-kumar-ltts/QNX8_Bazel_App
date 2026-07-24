# EM (Execution Manager)
add_executable(em main.cpp)

target_include_directories(em PRIVATE
    ${DLT_INCLUDE_DIR}
    ${NLOHMANN_JSON_INCLUDE_DIR}
)

target_link_libraries(em
    dlt
    Threads::Threads
)

# Copy manifest.json to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/manifest.json
    ${CMAKE_BINARY_DIR}/bin/manifest.json COPYONLY)
