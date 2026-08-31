#include "system_info.h"
#include "health_status.h"
#include "device_info.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <cstdlib>

TEST(SystemInfoTest, HostnameIsNotEmpty)
{
    const auto hostname = systeminfo::get_hostname();

    EXPECT_FALSE(hostname.empty());
}

TEST(SystemInfoTest, UptimeHasExpectedFormat)
{
    const auto uptime = systeminfo::get_uptime();

    EXPECT_NE(uptime.find("h"), std::string::npos);
    EXPECT_NE(uptime.find("m"), std::string::npos);
}

TEST(SystemInfoTest, MemoryUsageIsWithinValidRange)
{
    const auto memory_usage = systeminfo::get_memory_usage_percent();

    EXPECT_GE(memory_usage, 0.0);
    EXPECT_LE(memory_usage, 100.0);
}

TEST(SystemInfoTest, CpuUsageIsWithinValidRange)
{
    double cpu = systeminfo::get_cpu_usage_percent();

    EXPECT_GE(cpu, 0.0);
    EXPECT_LE(cpu, 100.0);
}


TEST(SystemInfoTest, DiskUsageIsWithinValidRange)
{
    double disk = systeminfo::get_disk_usage_percent();

    EXPECT_GE(disk, 0.0);
    EXPECT_LE(disk, 100.0);
}

TEST(HealthStatusTest, HealthyUsage)
{
    EXPECT_EQ(
        healthstatus::evaluate_usage(50.0),
        healthstatus::Status::Healthy
    );
}

TEST(HealthStatusTest, WarningUsage)
{
    EXPECT_EQ(
        healthstatus::evaluate_usage(80.0),
        healthstatus::Status::Warning
    );
}

TEST(HealthStatusTest, CriticalUsage)
{
    EXPECT_EQ(
        healthstatus::evaluate_usage(90.0),
        healthstatus::Status::Critical
    );
}

TEST(HealthStatusTest, InvalidUsageThrows)
{
    EXPECT_THROW(
        healthstatus::evaluate_usage(101.0),
        std::invalid_argument
    );
}


TEST(HealthStatusTest, JustBelowWarningIsHealthy)
{
    EXPECT_EQ(
        healthstatus::evaluate_usage(79.9),
        healthstatus::Status::Healthy
    );
}

TEST(HealthStatusTest, JustBelowCriticalIsWarning)
{
    EXPECT_EQ(
        healthstatus::evaluate_usage(89.9),
        healthstatus::Status::Warning
    );
}

TEST(HealthStatusTest, MaximumValidUsageIsCritical)
{
    EXPECT_EQ(
        healthstatus::evaluate_usage(100.0),
        healthstatus::Status::Critical
    );
}


TEST(HealthStatusTest, NegativeUsageThrows)
{
    EXPECT_THROW(
        healthstatus::evaluate_usage(-1.0),
        std::invalid_argument
    );
}
TEST(DeviceInfoTest, SimulatedDeviceDataIsValid)
{
const deviceinfo::SimulatedDevice device;
const auto data = device.read_data();
    EXPECT_GE(data.temperature_celsius, -40.0);
    EXPECT_LE(data.temperature_celsius, 125.0);

    EXPECT_GE(data.memory_usage_percent, 0.0);
    EXPECT_LE(data.memory_usage_percent, 100.0);

    EXPECT_GE(data.cpu_usage_percent, 0.0);
    EXPECT_LE(data.cpu_usage_percent, 100.0);

    EXPECT_GE(data.disk_usage_percent, 0.0);
    EXPECT_LE(data.disk_usage_percent, 100.0);
}

TEST(DeviceInfoTest, SimulatedDeviceDataHasExpectedValues)
{
const deviceinfo::SimulatedDevice device;
const auto data = device.read_data();
    EXPECT_DOUBLE_EQ(data.temperature_celsius, 65.0);
    EXPECT_DOUBLE_EQ(data.memory_usage_percent, 45.0);
    EXPECT_DOUBLE_EQ(data.cpu_usage_percent, 30.0);
    EXPECT_DOUBLE_EQ(data.disk_usage_percent, 55.0);
}


TEST(DeviceInfoTest, ReadsValuesFromEnvironment)
{
    setenv("DEVICE_TEMPERATURE", "85.0", 1);
    setenv("DEVICE_MEMORY", "82.0", 1);
    setenv("DEVICE_CPU", "91.0", 1);
    setenv("DEVICE_DISK", "75.0", 1);

const deviceinfo::SimulatedDevice device;
const auto data = device.read_data();
    EXPECT_DOUBLE_EQ(data.temperature_celsius, 85.0);
    EXPECT_DOUBLE_EQ(data.memory_usage_percent, 82.0);
    EXPECT_DOUBLE_EQ(data.cpu_usage_percent, 91.0);
    EXPECT_DOUBLE_EQ(data.disk_usage_percent, 75.0);

    unsetenv("DEVICE_TEMPERATURE");
    unsetenv("DEVICE_MEMORY");
    unsetenv("DEVICE_CPU");
    unsetenv("DEVICE_DISK");
}

TEST(DeviceInfoTest, InvalidEnvironmentValuesUseDefaults)
{
    setenv("DEVICE_TEMPERATURE", "not-a-number", 1);
    setenv("DEVICE_MEMORY", "invalid", 1);
    setenv("DEVICE_CPU", "bad-value", 1);
    setenv("DEVICE_DISK", "unknown", 1);

const deviceinfo::SimulatedDevice device;
const auto data = device.read_data();

    EXPECT_DOUBLE_EQ(data.temperature_celsius, 65.0);
    EXPECT_DOUBLE_EQ(data.memory_usage_percent, 45.0);
    EXPECT_DOUBLE_EQ(data.cpu_usage_percent, 30.0);
    EXPECT_DOUBLE_EQ(data.disk_usage_percent, 55.0);

    unsetenv("DEVICE_TEMPERATURE");
    unsetenv("DEVICE_MEMORY");
    unsetenv("DEVICE_CPU");
    unsetenv("DEVICE_DISK");
}

