cmake_minimum_required(VERSION 3.10)

# Set the project name
project(WifiNetworkManager)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(WifiNetworkManager
    src/main.cpp
    src/wifi_manager.cpp
    src/gui/gui_gtk.cpp
    src/utils/utils.cpp
    src/logger/logger.cpp
)

# Include directories
target_include_directories(WifiNetworkManager PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_BINARY_DIR}/ui"
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/src/gui"
    "${PROJECT_SOURCE_DIR}/src/utils"
    "${PROJECT_SOURCE_DIR}/src/logger"
)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
target_include_directories(WifiNetworkManager PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(WifiNetworkManager PRIVATE ${GTKMM_LIBRARIES})
