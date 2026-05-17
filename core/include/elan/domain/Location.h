#pragma once

#include "elan/domain/Hall.h"
#include "elan/common/Constants.h"
#include "elan/domain/Schedule.h"

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    class Location
    {
        int id;
        char address[constants::ADDRES_LENGTH];
        Hall halls[constants::MAX_HALLS];
        int hallCount = 0;
        Schedule schedule[constants::WORKING_DAYS][constants::WORKING_HOURS][constants::MAX_HALLS];

        void SetId(int id);
        int GetNextHallId();

        template <typename T>
        friend class storage::Storage;

    public:
        Location() = default;
        Location(const char *address);
        int GetId() const;

        bool AddHall(Hall &hall);
        bool RemoveHall(int hallId);
        int FindHallIndexById(int hallId);

        bool AddSchedule(const Schedule &schedule);
        bool RemoveSchedule(const Schedule &schedule);

        // Удаліть
        void PrintLocation();
        void PrintLocationHalls();
        void PrintLocationSchedule();
    };
}