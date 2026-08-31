#ifndef DEVICE_INFO_H
#define DEVICE_INFO_H

#include "device.h"

#include <string>

namespace deviceinfo
{
    class SimulatedDevice : public device::Device
    {
    public:
        DeviceData read_data() const override;
    };

    std::string device_data_to_string(const DeviceData& data);
}

#endif
