#include "device_info.h"

#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <string>

namespace
{
    double read_environment_value(const char* name, double default_value)
    {
        const char* value = std::getenv(name);

        if (value == nullptr)
        {
            return default_value;
        }

        try
        {
            return std::stod(value);
        }
        catch (...)
        {
            return default_value;
        }
    }
}

namespace deviceinfo
{
    DeviceData SimulatedDevice::read_data() const
{
    return {
        read_environment_value("DEVICE_TEMPERATURE", 65.0),
        read_environment_value("DEVICE_MEMORY", 45.0),
        read_environment_value("DEVICE_CPU", 30.0),
        read_environment_value("DEVICE_DISK", 55.0)
    };
}

    std::string device_data_to_string(const DeviceData& data)
    {
        std::ostringstream output;

        output << std::fixed << std::setprecision(1);
        output << "Temperature: " << data.temperature_celsius << " C\n";
        output << "Memory:     " << data.memory_usage_percent << "%\n";
        output << "CPU:        " << data.cpu_usage_percent << "%\n";
        output << "Disk:       " << data.disk_usage_percent << "%";

        return output.str();
    }
}
