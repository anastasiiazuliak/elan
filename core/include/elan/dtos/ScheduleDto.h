#pragma once

#include "elan/domain/Schedule.h"

namespace dtos
{
    struct ScheduleDto
    {
        int groupId;
        int hallId;
        int day;
        int time;
        bool isOccupied;
    };

    ScheduleDto ToDto(const domain::Schedule &s);
    domain::Schedule FromDto(const ScheduleDto &dto);
}