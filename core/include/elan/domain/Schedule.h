#pragma once

namespace domain
{
    enum class Day
    {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday
    };

    enum class Time
    {
        T08_00,
        T09_00,
        T10_00,
        T11_00,
        T12_00,
        T13_00,
        T14_00,
        T15_00,
        T16_00,
        T17_00,
        T18_00,
        T19_00,
        T20_00
    };

    struct Schedule
    {
        int id;
        int groupId = -1;
        int hallId;
        Day day;
        Time time;
        bool isOccupied = false;

    public:
        // Удаліть
        void PrintSchedule();
    };
}
