#pragma once

#include "elan/domain/Hall.h"
#include "elan/common/Constants.h"
#include "elan/domain/Schedule.h"

#include <vector>

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

        void SetAddress(const char* address);

        int GetId() const;
        const char *GetAddress() const;
        int GetHallCount() const;
        std::vector<Hall> Location::GetHalls() const;

        bool AddHall(Hall &hall);
        bool RemoveHall(int hallId);
        bool Location::UpdateHall(int hallId, const char *name, int capacity);
        const Hall* GetHallById(int hallId) const;
        int FindHallIndexById(int hallId) const;

        bool AddSchedule(const Schedule &schedule);
        bool RemoveSchedule(const Schedule &schedule);
        std::vector<Schedule> Location::GetScheduleList() const;

        // Удаліть
        void PrintLocation();
        void PrintLocationHalls();
        void PrintLocationSchedule();
    };
}