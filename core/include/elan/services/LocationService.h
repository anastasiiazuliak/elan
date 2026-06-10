#pragma once

#include "elan/domain/Location.h"
#include "elan/storage/Storages.h"

namespace service
{
    class LocationService
    {
    public:
        static bool AddHall(int locationId, domain::Hall &hall);
        static bool RemoveHall(int locationId, int hallId);
        static bool UpdateHall(int locationId, int hallId, const char *name,int capacity);

        static bool AddSchedule(int locationId, const domain::Schedule &s);
        static bool RemoveSchedule(int locationId, const domain::Schedule &s);
        static std::vector<domain::Schedule> GetScheduleByHall(int locationId, int hallId);
        static std::vector<domain::Schedule> GetScheduleByDay(int locationId, domain::Day day);
        static std::vector<domain::Schedule> GetScheduleByGroup(int locationId, int groupId);
    };
}