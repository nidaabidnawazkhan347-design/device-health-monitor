#!/bin/bash

echo "================================="
echo "      Device Health Check"
echo "================================="

output=$(./build/device-monitor)
status=$?

echo "$output"

if [ $status -ne 0 ]; then
    echo "[FAIL] Device monitor failed"
    exit 1
fi

echo "[PASS] Device monitor completed successfully"

memory=$(echo "$output" | grep "Memory Usage" | awk '{print $3}' | tr -d '%')

if awk "BEGIN {exit !($memory >= 0 && $memory <= 100)}"; then
    echo "[PASS] Memory usage is within valid range"
else
    echo "[FAIL] Memory usage is outside valid range"
    exit 1
fi

cpu=$(echo "$output" | grep "CPU Usage" | awk '{print $3}' | tr -d '%')

if awk "BEGIN {exit !($cpu >= 0 && $cpu <= 100)}"; then
    echo "[PASS] CPU usage is within valid range"
else
    echo "[FAIL] CPU usage is outside valid range"
    exit 1
fi
