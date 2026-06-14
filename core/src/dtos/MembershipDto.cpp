#include "elan/dtos/MembershipDto.h"
#include "elan/domain/Membership.h"

namespace dtos
{
    MembershipDto ToDto(const domain::Membership &m)
    {
        return {
            m.GetId(),
            m.GetClientId(),
            m.GetGroupId(),
            m.GetSubscriptionId(),
            m.GetStartDate(),
            m.GetEndDate(),
            m.GetRemainingWorkouts(),
            m.GetCompletedWorkouts()
        };
    }
}