#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <string>

namespace systeminfo
{
    std::string get_hostname();
    std::string get_uptime();
    double get_memory_usage_percent();
    double get_cpu_usage_percent();
    double get_disk_usage_percent();
}

#endif
