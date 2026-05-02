#pragma once 

namespace common
{
    struct Time
    {
        int hour;
        int minutes;

        Time();
        Time(int hour, int minutes);
    };
    bool IsTimeValid(int hour, int minutes);
}