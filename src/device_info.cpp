#include "device_info.h"

#include <iomanip>
#include <sstream>

namespace deviceinfo
{
    DeviceData get_simulated_device_data()
    {
        return {
            65.0,
            45.0,
            30.0,
            55.0
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

