#pragma once

#include "elan/domain/Location.h"
#include "elan/storage/Storage.h"

namespace service
{
    class LocationService
    {
        static storage::Storage<domain::Location> locations;

    public:
        bool AddHall(int locationId, domain::Hall &hall);
        bool RemoveHall(int locationId, int hallId);

        bool AddSchedule(int locationId, const domain::Schedule &s);
        bool RemoveSchedule(int locationId, const domain::Schedule &s);
    };
}