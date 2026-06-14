#pragma once

#include <vector>

#include "elan/domain/Membership.h"
#include "elan/common/Date.h"

namespace dtos
{
    struct MembershipDto
    {
        int id;

        int clientId;
        int groupId;
        int subscriptionId;

        common::Date startDate;
        common::Date endDate;

        int remainingWorkouts;
        int completedWorkouts;
    };

    MembershipDto ToDto(const domain::Membership &m);
}