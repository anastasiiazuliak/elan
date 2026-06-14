#pragma once

#include <vector>
#include "elan/domain/Membership.h"

namespace service
{
    class MembershipService
    {
    public:
        static bool CreateMembership(int clientId, int groupId, int subscriptionId);

        static bool UseWorkout(int membershipId);

        static std::vector<domain::Membership> GetByClient(int clientId);

        static std::vector<domain::Membership> GetByGroup(int groupId);

        static std::vector<domain::Membership> GetActiveByClient(int clientId);

        static std::vector<domain::Membership> GetActiveByGroup(int groupId);
    };
}