#include "health_status.h"

#include <stdexcept>

namespace healthstatus
{
    Status evaluate_usage(double usage_percent)
    {
        if (usage_percent < 0.0 || usage_percent > 100.0)
        {
            throw std::invalid_argument("Usage percentage must be between 0 and 100");
        }

        if (usage_percent >= 90.0)
        {
            return Status::Critical;
        }

        if (usage_percent >= 80.0)
        {
            return Status::Warning;
        }

        return Status::Healthy;
    }

    std::string status_to_string(Status status)
    {
        switch (status)
        {
            case Status::Healthy:
                return "HEALTHY";

            case Status::Warning:
                return "WARNING";

            case Status::Critical:
                return "CRITICAL";
        }

        throw std::invalid_argument("Unknown health status");
    }
}
