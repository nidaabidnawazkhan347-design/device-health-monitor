#!/bin/bash

echo "================================="
echo "      Device Health Check"
echo "================================="

./build/device-monitor

if [ $? -eq 0 ]; then
    echo "[PASS] Device monitor completed successfully"
else
    echo "[FAIL] Device monitor failed"
    exit 1
fi
