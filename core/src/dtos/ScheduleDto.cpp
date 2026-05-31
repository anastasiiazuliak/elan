#include "elan/dtos/ScheduleDto.h"

namespace dtos
{
    ScheduleDto ToDto(const domain::Schedule &s)
    {
        return {
            s.groupId,
            s.hallId,
            static_cast<int>(s.day),
            static_cast<int>(s.time),
            s.isOccupied
        };
    }

    domain::Schedule FromDto(const ScheduleDto &dto)
    {
        domain::Schedule s;

        s.groupId = dto.groupId;
        s.hallId = dto.hallId;
        s.day = static_cast<domain::Day>(dto.day);
        s.time = static_cast<domain::Time>(dto.time);
        s.isOccupied = dto.isOccupied;

        return s;
    }
}