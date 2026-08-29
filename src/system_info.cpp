#include "system_info.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>

namespace systeminfo
{
    std::string get_hostname()
    {
        char hostname[256];

        if (gethostname(hostname, sizeof(hostname)) != 0)
        {
            throw std::runtime_error("Failed to read hostname");
        }

        hostname[sizeof(hostname) - 1] = '\0';

        return std::string(hostname);
    }

    std::string get_uptime()
    {
        std::ifstream uptime_file("/proc/uptime");

        if (!uptime_file)
        {
            throw std::runtime_error("Failed to open /proc/uptime");
        }

        double uptime_seconds = 0.0;
        uptime_file >> uptime_seconds;

        if (!uptime_file)
        {
            throw std::runtime_error("Failed to read uptime");
        }

        const auto total_seconds =
            static_cast<long long>(uptime_seconds);

        const auto hours = total_seconds / 3600;
        const auto minutes = (total_seconds % 3600) / 60;

        std::ostringstream result;
        result << hours << "h " << minutes << "m";

        return result.str();
    }

    double get_memory_usage_percent()
    {
        std::ifstream memory_file("/proc/meminfo");

        if (!memory_file)
        {
            throw std::runtime_error("Failed to open /proc/meminfo");
        }

        long long total_kb = 0;
        long long available_kb = 0;

        std::string key;
        long long value;
        std::string unit;

        while (memory_file >> key >> value >> unit)
        {
            if (key == "MemTotal:")
            {
                total_kb = value;
            }
            else if (key == "MemAvailable:")
            {
                available_kb = value;
            }
        }

        if (total_kb <= 0 || available_kb < 0 || available_kb > total_kb)
        {
            throw std::runtime_error("Invalid memory information");
        }

        const double used_kb = total_kb - available_kb;

        return (used_kb / total_kb) * 100.0;
    }
}
