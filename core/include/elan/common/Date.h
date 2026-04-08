#pragma once

namespace common
{
    struct Date
    {
        int Day;
        int Month;
        int Year;

        Date();
        Date(int day, int month, int year);
    };

    bool isDateValid(int day, int month, int year);
}
