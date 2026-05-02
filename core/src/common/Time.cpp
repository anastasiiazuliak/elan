#include "elan/common/Time.h"

namespace common
{
    Time::Time()
    {
        hour = 1;
        minutes = 1;
    };

    bool isTimeValid(int hour, int minutes) {

    };

    Time::Time(int hour, int minutes)
    {
        if (isTimeValid(hour, minutes))
        {
            this->hour = hour;
            this->minutes = minutes;
        }
        else
        {
            this->hour = 10;
            this->minutes = 00;
        }
    };
}
