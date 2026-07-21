cmake_minimum_required(VERSION 3.20)
project(qnx_diag_app CXX)

set(CMAKE_CXX_STANDARD 17)

# Point to internal dependencies
include_directories(${CMAKE_SOURCE_DIR}/third_party/dlt/include)
link_directories(${CMAKE_SOURCE_DIR}/third_party/dlt/lib)

# Compile target binary
add_executable(diag_app src/diag_main.cpp)
target_link_libraries(diag_app dlt)
