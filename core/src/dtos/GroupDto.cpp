#include "elan/dtos/GroupDto.h"

namespace dtos
{
    GroupDto ToDto(const domain::Group &g)
    {
        return {
            g.GetId(),
            g.GetName(),
            g.GetCoachId(),
            g.GetStyleId(),
            g.GetSkillLevel(),
            g.GetCategory(),
            g.GetSubscriptionCount(),
            g.GetSubscriptionIds()
        };
    }

    domain::Group FromDto(const GroupDto &dto)
    {
        domain::Group group(
            dto.name.c_str(),
            dto.coachId,
            dto.styleId,
            dto.skillLevel,
            dto.category
        );

        for (int subscriptionId : dto.subscriptionIds)
        {
            group.AddSubscription(subscriptionId);
        }

        return group;
    }
}
