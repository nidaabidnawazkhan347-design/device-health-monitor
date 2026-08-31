#include "system_info.h"
#include "health_status.h"

#include <gtest/gtest.h>
#include <stdexcept>

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
