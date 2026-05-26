#include "elan/domain/Location.h"
#include <cstring>

#include <iostream>

namespace domain
{
    Location::Location(const char *address)
    {
        std::strncpy(this->address, address, constants::ADDRES_LENGTH);
        this->address[constants::ADDRES_LENGTH - 1] = '\0';

        hallCount = 0;

        for (int d = 0; d < constants::WORKING_DAYS; d++)
            for (int t = 0; t < constants::WORKING_HOURS; t++)
                for (int h = 0; h < constants::MAX_HALLS; h++)
                    schedule[d][t][h].isOccupied = false;
    }

    int Location::GetNextHallId()
    {
        int maxId = 0;

        for (int i = 0; i < hallCount; i++)
        {
            if (halls[i].id > maxId)
            {
                maxId = halls[i].id;
            }
        }

        return maxId + 1;
    }

    bool Location::AddHall(Hall &hall)
    {
        hall.id = GetNextHallId();
        if (hallCount >= constants::MAX_HALLS)
            return false;

        for (int i = 0; i < hallCount; i++)
        {
            if (halls[i].id == hall.id)
                return false;
        }

        halls[hallCount++] = hall;
        return true;
    }

    bool Location::RemoveHall(int hallId)
    {
        int index = -1;

        for (int i = 0; i < hallCount; i++)
        {
            if (halls[i].id == hallId)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            return false;
        }

        for (int i = index; i < hallCount - 1; i++)
        {
            halls[i] = halls[i + 1];
        }

        hallCount--;

        return true;
    }

    int Location::FindHallIndexById(int hallId)
    {
        for (int i = 0; i < hallCount; i++)
        {
            if (halls[i].id == hallId)
            {
                return i;
            }
        }

        return -1;
    }

    bool Location::AddSchedule(const Schedule &s)
    {
        int d = static_cast<int>(s.day);
        int t = static_cast<int>(s.time);

        int hallIndex = FindHallIndexById(s.hallId);

        if (hallIndex == -1)
        {
            return false;
        }

        if (schedule[d][t][hallIndex].isOccupied)
        {
            return false;
        }

        schedule[d][t][hallIndex] = s;
        schedule[d][t][hallIndex].isOccupied = true;

        return true;
    }

    bool Location::RemoveSchedule(const Schedule &s)
    {
        int d = static_cast<int>(s.day);
        int t = static_cast<int>(s.time);

        int hallIndex = FindHallIndexById(s.hallId);

        if (hallIndex == -1)
        {
            return false;
        }

        if (!schedule[d][t][hallIndex].isOccupied)
        {
            return false;
        }

        schedule[d][t][hallIndex] = Schedule(); // очищаємо слот

        return true;
    }

    void Location::SetId(int id)
    {
        this->id = id;
    }

    int Location::GetId() const
    {
        return id;
    }

    const char *Location::GetAddress() const
    {
        return address;
    }

    int Location::GetHallCount() const
    {
        return hallCount;
    }

    // Удаліть
    void Location::PrintLocation()
    {
        std::cout << "========== LOCATION ==========\n";

        std::cout << "ID: " << id << "\n";
        std::cout << "Address: " << address << "\n";

        std::cout << "Halls count: " << hallCount << "\n";

        std::cout << "\n";
    }

    void Location::PrintLocationHalls()
    {
        std::cout << "========== HALLS ==========\n";

        if (hallCount == 0)
        {
            std::cout << "No halls available\n";
            return;
        }

        for (int i = 0; i < hallCount; i++)
        {
            std::cout << "Hall #" << i + 1 << "\n";
            halls[i].PrintHall();
            std::cout << "--------------------------\n";
        }
    }

    void Location::PrintLocationSchedule()
    {
        std::cout << "========== SCHEDULE ==========\n";

        bool empty = true;

        for (int d = 0; d < constants::WORKING_DAYS; d++)
        {
            for (int t = 0; t < constants::WORKING_HOURS; t++)
            {
                for (int h = 0; h < hallCount; h++)
                {
                    if (schedule[d][t][h].isOccupied)
                    {
                        empty = false;
                        schedule[d][t][h].PrintSchedule();
                    }
                }
            }
        }

        if (empty)
        {
            std::cout << "No scheduled sessions\n";
        }

        std::cout << "\n";
    }
}