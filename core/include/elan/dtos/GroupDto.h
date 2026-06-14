#pragma once

#include "elan/domain/Group.h"
#include <string>
#include <vector>

namespace dtos
{
    struct GroupDto
    {
        int id;
        std::string name;
        int coachId;
        int styleId;
        domain::SkillLevel skillLevel;
        common::Category category;

        int subscriptionCount;
        std::vector<int> subscriptionIds;
    };

    GroupDto ToDto(const domain::Group &g);
    domain::Group FromDto(const GroupDto &dto);
}
