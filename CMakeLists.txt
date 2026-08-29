cmake_minimum_required(VERSION 3.20)

project(DeviceHealthMonitor VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(device-monitor
    src/main.cpp
    src/system_info.cpp
)

target_include_directories(device-monitor
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(system-info-tests
    tests/system_info_test.cpp
    src/system_info.cpp
)

target_include_directories(system-info-tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(system-info-tests
    PRIVATE
        gtest
        gtest_main
)

include(GoogleTest)

gtest_discover_tests(system-info-tests)
