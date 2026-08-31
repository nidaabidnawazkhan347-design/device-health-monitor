#ifndef DEVICE_DATA_H
#define DEVICE_DATA_H

namespace deviceinfo
{
    struct DeviceData
    {
        double temperature_celsius;
        double memory_usage_percent;
        double cpu_usage_percent;
        double disk_usage_percent;
    };
}

#endif
