cmake_minimum_required(VERSION 3.15)
project(diag_app LANGUAGES C CXX)

# Force C++17 standard (avoids the "lang-c++ is deprecated" warning in QNX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Define the executable and source files
add_executable(diag_app 
    diag_main.cpp
)

# 2. Configure Include Directories
# Added the explicit path to the generated dlt folder
target_include_directories(diag_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    /home/prathik/qnx800/QNX8_App/dlt-daemon/include
    /home/prathik/qnx800/QNX8_App/dlt-daemon/include/dlt
    /home/prathik/qnx800/QNX8_App/dlt-daemon/build/include
    /home/prathik/qnx800/QNX8_App/dlt-daemon/build/include/dlt
)

# 3. Configure External Library Paths
# Tells the linker where to find your custom built libdlt.so
target_link_directories(diag_app PRIVATE
    /home/prathik/qnx800/QNX8_App/dlt-daemon/build/src/lib
)

# 4. Link Libraries
# Fixes the 'recv' error by adding socket, and adds dlt for logging
target_link_libraries(diag_app PRIVATE
    socket
    dlt
)
