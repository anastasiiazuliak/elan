#include "elan/domain/Schedule.h"

#include <iostream>

namespace domain 
{

    //Удаліть
    void Schedule::PrintSchedule()
    {
        std::cout << "========== SCHEDULE ==========\n";

        std::cout << "ID: " << id << "\n";

        std::cout << "Group ID: " << groupId << "\n";
        std::cout << "Hall ID: " << hallId << "\n";

        std::cout << "Day: ";

        switch (day)
        {
        case Day::Monday:
            std::cout << "Monday";
            break;
        case Day::Tuesday:
            std::cout << "Tuesday";
            break;
        case Day::Wednesday:
            std::cout << "Wednesday";
            break;
        case Day::Thursday:
            std::cout << "Thursday";
            break;
        case Day::Friday:
            std::cout << "Friday";
            break;
        case Day::Saturday:
            std::cout << "Saturday";
            break;
        }

        std::cout << "\nTime: ";

        switch (time)
        {
        case Time::T08_00: std::cout << "08:00"; break;
        case Time::T09_00: std::cout << "09:00"; break;
        case Time::T10_00: std::cout << "10:00"; break;
        case Time::T11_00: std::cout << "11:00"; break;
        case Time::T12_00: std::cout << "12:00"; break;
        case Time::T13_00: std::cout << "13:00"; break;
        case Time::T14_00: std::cout << "14:00"; break;
        case Time::T15_00: std::cout << "15:00"; break;
        case Time::T16_00: std::cout << "16:00"; break;
        case Time::T17_00: std::cout << "17:00"; break;
        case Time::T18_00: std::cout << "18:00"; break;
        case Time::T19_00: std::cout << "19:00"; break;
        case Time::T20_00: std::cout << "20:00"; break;
        }

        std::cout << "\nOccupied: "
                  << (isOccupied ? "Yes" : "No")
                  << "\n";

        std::cout << "\n";
    }
}