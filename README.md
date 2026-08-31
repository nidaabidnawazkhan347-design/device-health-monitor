# Device Health Monitor
[![Device Health Monitor CI](https://github.com/nidaabidnawazkhan347-design/device-health-monitor/actions/workflows/ci.yml/badge.svg)](https://github.com/nidaabidnawazkhan347-design/device-health-monitor/actions/workflows/ci.yml)

A Linux-based C++ application that monitors basic system health information such as hostname, uptime, memory usage, CPU usage, and disk usage.

The project also includes automated GoogleTest tests, a Bash health-check script, and GitHub Actions CI.

## Features

- Hostname monitoring
- System uptime monitoring
- Memory usage monitoring
- CPU usage monitoring
- Disk usage monitoring
- Automated GoogleTest tests
- Bash health-check script
- GitHub Actions continuous integration

## Example Output

```text
================================
      Device Health Monitor
================================

Hostname:       DESKTOP-V0BBSC7
Uptime:         7h 47m
Memory Usage:   7.5% [HEALTHY]
CPU Usage:      0.0% [HEALTHY]
Disk Usage:     5.3% [HEALTHY]

Overall Status: HEALTHY
```

## Requirements

- Linux
- C++ compiler with C++17 support
- CMake
- GoogleTest
- Bash

### Ubuntu / Debian

Install the required packages with:

    sudo apt update
    sudo apt install -y cmake g++ libgtest-dev

## Build

    cmake -S . -B build
    cmake --build build

## Run

    ./build/device-monitor

Example output:

    =================================
          Device Health Monitor
    =================================

    Hostname:       DESKTOP-V0BBSC7
    Uptime:         6h 43m
    Memory Usage:   7.3%
    CPU Usage:      0.0%
    Disk Usage:     5.3%

## Testing

Build the project and run the automated tests with:

    cmake --build build
    cd build
    ctest --output-on-failure

The project currently includes five GoogleTest tests covering:

- Hostname is not empty
- Uptime format
- Memory usage is within the valid range
- CPU usage is within the valid range
- Disk usage is within the valid range

A successful test run should report:

    100% tests passed, 0 tests failed out of 9

## Project Structure

```text
device-health-monitor/
├── src/
│   ├── main.cpp
│   ├── system_info.cpp
│   ├── system_info.h
│   ├── health_status.cpp
│   └── health_status.h
├── tests/
│   └── system_info_test.cpp
├── scripts/
│   └── health_check.sh
├── .github/
│   └── workflows/
│       └── ci.yml
├── CMakeLists.txt
└── README.md
```

## Health Check Script

The project includes a Bash script that runs the device monitor and validates memory, CPU, and disk usage.

Run it from the project root with:

    ./scripts/health_check.sh

The script reports PASS or FAIL for each health check.

Example:

    [PASS] Device monitor completed successfully
    [PASS] Memory usage is within valid range
    [PASS] CPU usage is within valid range
    [PASS] Disk usage is within valid range

## Continuous Integration

GitHub Actions automatically builds and tests the project whenever changes are pushed to the `main` branch or a pull request is opened against `main`.

The CI workflow:

1. Checks out the repository
2. Installs CMake, G++, and GoogleTest
3. Configures the project with CMake
4. Builds the application and tests
5. Runs all GoogleTest tests
6. Runs the health-check script

Workflow file:

    .github/workflows/ci.yml
