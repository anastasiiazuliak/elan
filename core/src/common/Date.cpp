#include <iostream>
#include <ctime>
#include "elan/common/Date.h"

namespace common
{
    Date::Date()
    {
        day = 1;
        month = 1;
        year = 2000;
    };

    bool isDateValid(int day, int month, int year)
    {
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);
        int currentYear = now->tm_year + 1900;

        if (year < 1930 || year > currentYear - 3)
            return false;
        if (month < 1 || month > 12)
            return false;

        int daysInMonth = 31;

        if (month == 2)
            daysInMonth = 28;
        else if (month == 4 || month == 6 || month == 9 || month == 11)
            daysInMonth = 30;

        return day >= 1 && day <= daysInMonth;
    };

    Date::Date(int day, int month, int year)
    {
        if (isDateValid(day, month, year))
        {
            this->day = day;
            this->month = month;
            this->year = year;
        }
        else
        {
            this->day = 1;
            this->month = 1;
            this->year = 2000;
        }
    };
}