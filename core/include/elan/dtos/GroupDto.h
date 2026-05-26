#pragma once

#include "elan/domain/Group.h"

namespace dtos
{
    struct GroupDto
    {
        int id;
        int coachId;
        int styleId;
        domain::SkillLevel skillLevel;
        int clientCount;
    };

    GroupDto ToDto(const domain::Group &g);
    domain::Group FromDto(const GroupDto &dto);
}