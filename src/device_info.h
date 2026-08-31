#ifndef DEVICE_INFO_H
#define DEVICE_INFO_H

#include <string>

namespace deviceinfo
{
    struct DeviceData
    {
        double temperature_celsius;
        double memory_usage_percent;
        double cpu_usage_percent;
        double disk_usage_percent;
    };

    DeviceData get_simulated_device_data();

    std::string device_data_to_string(const DeviceData& data);
}

#endif
