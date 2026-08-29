cmake_minimum_required(VERSION 3.20)

project(DeviceHealthMonitor VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(device-monitor
    src/main.cpp
    src/system_info.cpp
)

target_include_directories(device-monitor
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
