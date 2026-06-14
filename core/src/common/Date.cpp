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
    }

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
    }

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
    }

    Date Today()
    {
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);

        return Date(
            now->tm_mday,
            now->tm_mon + 1,
            now->tm_year + 1900
        );
    }

    static int DaysInMonth(int month, int year)
    {
        int daysInMonth = 31;

        if (month == 2)
        {
            bool leap =
                (year % 4 == 0 && year % 100 != 0) ||
                (year % 400 == 0);

            daysInMonth = leap ? 29 : 28;
        }
        else if (month == 4 || month == 6 ||
                 month == 9 || month == 11)
        {
            daysInMonth = 30;
        }

        return daysInMonth;
    }

    Date AddDays(const Date &d, int days)
    {
        Date result = d;
        result.day += days;

        while (result.day > DaysInMonth(result.month, result.year))
        {
            result.day -= DaysInMonth(result.month, result.year);
            result.month++;

            if (result.month > 12)
            {
                result.month = 1;
                result.year++;
            }
        }

        return result;
    }

    Date ParseDate(const std::string &str)
    {
        Date d;

        sscanf(
            str.c_str(),
            "%d-%d-%d",
            &d.year,
            &d.month,
            &d.day);

        return d;
    }

    std::string FormatDate(const Date &d)
    {
        char buffer[11];

        sprintf(
            buffer,
            "%04d-%02d-%02d",
            d.year,
            d.month,
            d.day);

        return std::string(buffer);
    }
}