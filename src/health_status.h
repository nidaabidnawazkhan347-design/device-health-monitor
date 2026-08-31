#ifndef HEALTH_STATUS_H
#define HEALTH_STATUS_H

#include <string>

namespace healthstatus
{
    enum class Status
    {
        Healthy,
        Warning,
        Critical
    };

    Status evaluate_usage(double usage_percent);

    std::string status_to_string(Status status);
}

#endif
