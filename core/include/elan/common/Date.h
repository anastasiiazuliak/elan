#pragma once

namespace common
{
    struct Date
    {
        int day;
        int month;
        int year;

        Date();
        Date(int day, int month, int year);
    };

    bool isDateValid(int day, int month, int year);
    Date ParseDate(const std::string &str);
    std::string FormatDate(const Date &d);
}
