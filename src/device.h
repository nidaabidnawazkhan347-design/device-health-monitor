#ifndef DEVICE_H
#define DEVICE_H

#include "device_data.h"

namespace device
{
    class Device
    {
    public:
        virtual ~Device() = default;

        virtual deviceinfo::DeviceData read_data() const = 0;
    };
}

#endif
