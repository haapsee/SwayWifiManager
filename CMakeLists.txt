cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SwayWifiManager)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(SwayWifiManager
    src/main.cpp
)

# Include directories
target_include_directories(SwayWifiManager PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/src"
)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
target_include_directories(SwayWifiManager PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(SwayWifiManager PRIVATE ${GTKMM_LIBRARIES})
