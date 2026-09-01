#include "device.h"
#include "device_info.h"
#include "health_status.h"
#include "system_info.h"

#include <iomanip>
#include <iostream>

int main()
{
    try
    {
        const deviceinfo::SimulatedDevice simulated_device;
        const device::Device& device = simulated_device;

        const auto device_data = device.read_data();
        const auto hostname = systeminfo::get_hostname();
        const auto uptime = systeminfo::get_uptime();

        const auto memory = device_data.memory_usage_percent;
        const auto cpu = device_data.cpu_usage_percent;
        const auto disk = device_data.disk_usage_percent;

        const auto memory_status = healthstatus::evaluate_usage(memory);
        const auto cpu_status = healthstatus::evaluate_usage(cpu);
        const auto disk_status = healthstatus::evaluate_usage(disk);

        auto overall_status = healthstatus::Status::Healthy;

        if (memory_status == healthstatus::Status::Critical ||
            cpu_status == healthstatus::Status::Critical ||
            disk_status == healthstatus::Status::Critical)
        {
            overall_status = healthstatus::Status::Critical;
        }
        else if (memory_status == healthstatus::Status::Warning ||
                 cpu_status == healthstatus::Status::Warning ||
                 disk_status == healthstatus::Status::Warning)
        {
            overall_status = healthstatus::Status::Warning;
        }

        std::cout << "================================\n";
        std::cout << "      Device Health Monitor\n";
        std::cout << "================================\n\n";

        std::cout << "Hostname:       " << hostname << '\n';
        std::cout << "Uptime:         " << uptime << '\n';

        std::cout << std::fixed << std::setprecision(1);

        std::cout << "Memory Usage:   " << memory << "% ["
                  << healthstatus::status_to_string(memory_status) << "]\n";

        std::cout << "CPU Usage:      " << cpu << "% ["
                  << healthstatus::status_to_string(cpu_status) << "]\n";

        std::cout << "Disk Usage:     " << disk << "% ["
                  << healthstatus::status_to_string(disk_status) << "]\n";

        std::cout << "\nOverall Status: "
                  << healthstatus::status_to_string(overall_status)
                  << '\n';

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "ERROR: " << error.what() << '\n';
        return 1;
    }
}
