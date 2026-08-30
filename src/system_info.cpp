#include <fstream>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <sys/statvfs.h>

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

    double get_cpu_usage_percent()
    {
        std::ifstream stat_file("/proc/stat");

        if (!stat_file)
        {
            throw std::runtime_error("Failed to open /proc/stat");
        }

        std::string cpu;
        long long user;
        long long nice;
        long long system;
        long long idle;
        long long iowait;
        long long irq;
        long long softirq;
        long long steal;

        stat_file >> cpu >> user >> nice >> system >> idle
                  >> iowait >> irq >> softirq >> steal;

        const long long idle_time = idle + iowait;
        const long long total_time =
            user + nice + system + idle + iowait + irq + softirq + steal;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        stat_file.close();
        stat_file.open("/proc/stat");

        if (!stat_file)
        {
            throw std::runtime_error("Failed to reopen /proc/stat");
        }

        stat_file >> cpu >> user >> nice >> system >> idle
                  >> iowait >> irq >> softirq >> steal;

        const long long new_idle_time = idle + iowait;
        const long long new_total_time =
            user + nice + system + idle + iowait + irq + softirq + steal;

        const long long total_delta = new_total_time - total_time;
        const long long idle_delta = new_idle_time - idle_time;

        if (total_delta <= 0)
        {
            throw std::runtime_error("Invalid CPU statistics");
        }

        return (1.0 - (static_cast<double>(idle_delta) / total_delta)) * 100.0;
    }
double get_disk_usage_percent()
{
    std::ifstream disk_file("/proc/mounts");

    if (!disk_file)
    {
        throw std::runtime_error("Failed to open /proc/mounts");
    }

    struct statvfs disk_info{};

    if (statvfs("/", &disk_info) != 0)
    {
        throw std::runtime_error("Failed to read disk information");
    }

    const double total_bytes =
        static_cast<double>(disk_info.f_blocks) * disk_info.f_frsize;

    const double available_bytes =
        static_cast<double>(disk_info.f_bavail) * disk_info.f_frsize;

    if (total_bytes <= 0.0 || available_bytes < 0.0 ||
        available_bytes > total_bytes)
    {
        throw std::runtime_error("Invalid disk information");
    }

    const double used_bytes = total_bytes - available_bytes;

    return (used_bytes / total_bytes) * 100.0;
}

}
