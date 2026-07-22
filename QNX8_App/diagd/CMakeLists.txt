cmake_minimum_required(VERSION 3.15)
project(diagd LANGUAGES C CXX)

# Force C++17 standard (avoids the "lang-c++ is deprecated" warning in QNX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Define the executable (Change diag_main.cpp to main.cpp if you renamed it)
add_executable(diagd 
    daigd_main.cpp
)

# 2. Configure Include Directories
target_include_directories(diagd PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    /home/prathik/qnx800/QNX8_App/dlt-daemon/include
    /home/prathik/qnx800/QNX8_App/dlt-daemon/include/dlt
    /home/prathik/qnx800/QNX8_App/dlt-daemon/build/include
    /home/prathik/qnx800/QNX8_App/dlt-daemon/build/include/dlt
)

# 3. Configure External Library Paths
target_link_directories(diagd PRIVATE
    /home/prathik/qnx800/QNX8_App/dlt-daemon/build/src/lib
)

# 4. Link Libraries
target_link_libraries(diagd PRIVATE
    socket
    dlt
)
