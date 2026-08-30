#include "system_info.h"

#include <iomanip>
#include <iostream>

int main()
{
    try
    {
        std::cout << "================================\n";
        std::cout << "      Device Health Monitor\n";
        std::cout << "================================\n\n";

        std::cout << "Hostname:       "
                  << systeminfo::get_hostname() << '\n';

        std::cout << "Uptime:         "
                  << systeminfo::get_uptime() << '\n';

        std::cout << std::fixed << std::setprecision(1);

        std::cout << "Memory Usage:   "
                  << systeminfo::get_memory_usage_percent()
                  << "%\n";

        std::cout << "CPU Usage:      "
                  << systeminfo::get_cpu_usage_percent()
                  << "%\n";



        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "ERROR: " << error.what() << '\n';
        return 1;
  }

}
