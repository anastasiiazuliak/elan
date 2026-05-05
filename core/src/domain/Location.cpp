#include "elan/domain/Location.h"
#include <cstring>

namespace domain
{
    Location::Location(const char *address)
    {
        std::strncpy(this->address, address, constants::ADDRES_LENGTH);
        this->address[constants::ADDRES_LENGTH - 1] = '\0';

        hallCount = 0;
    }

    bool Location::AddHall(Hall &hall)
    {
        if (hallCount >= constants::MAX_HALLS)
        {
            return false;
        }

        if (hallCount == 0)
        {
            halls[hallCount] = hall;
            hallCount++;
        }
        else
        {
            for (int i = 0; i < hallCount; i++)
            {
                halls[i].GetId() == hall.GetId();
                return false;
            }
        }
    }

    bool Location::RemoveHall(int hallId)
    {
        int index = -1;

        for (int i = 0; i < hallCount; i++)
        {
            if (halls[i].GetId() == hallId)
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
            if (halls[i].GetId() == hallId)
            {
                return i;
            }
        }

        return -1;
    }

    bool Location::AddSchedule(Schedule &s)
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

    bool Location::RemoveSchedule(Schedule &s)
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
}