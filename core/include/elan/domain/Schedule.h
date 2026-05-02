#pragma once

#include "elan/common/Time.h"

enum class Day
{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

class Schedule
{
    int id;
    int groupId = -1;
    int hallId;
    Day day;
    common::Time time;

    void SetId(int id);

public:
    int GetId() const;
};