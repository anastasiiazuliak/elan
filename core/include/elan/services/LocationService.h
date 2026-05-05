#pragma once

#include "elan/domain/Location.h"

namespace service
{
    class LocationService
    {
    public:
        bool AddHall(int locationId, domain::Hall& hall);
        bool RemoveHall(int locationId, int hallId);

        bool AddSchedule(int locationId, Schedule s);
        bool RemoveSchedule(int locationId, Schedule s);
    };
}