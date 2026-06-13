#pragma once

#include "elan/domain/Group.h"
#include <string>

namespace dtos
{
    struct GroupDto
    {
        int id;
        std::string name;
        int coachId;
        int styleId;
        domain::SkillLevel skillLevel;
        int clientCount;
        std::vector<int> clientIds;
    };

    GroupDto ToDto(const domain::Group &g);
    domain::Group FromDto(const GroupDto &dto);
}