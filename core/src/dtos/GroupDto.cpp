#include "elan/dtos/GroupDto.h"

namespace dtos
{
    GroupDto ToDto(const domain::Group &g)
    {
        return {
            g.GetId(),
            g.GetCoachId(),
            g.GetStyleId(),
            g.GetSkillLevel(),
            g.GetClientCount()};
    }

    domain::Group FromDto(const GroupDto &dto)
    {
        return domain::Group(
            dto.coachId,
            dto.styleId,
            dto.skillLevel);
    }
}
