#include "system_info.h"

#include <gtest/gtest.h>

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
