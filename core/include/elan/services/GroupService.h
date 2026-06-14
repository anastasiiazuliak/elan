#pragma once

#include "elan/storage/Storages.h"
#include "elan/domain/Group.h"
#include "elan/services/LocationService.h"

namespace service
{
    class GroupService
    {
    public:
        static std::vector<domain::Group> GetGroupsByCoachId(int id);
        static std::vector<int> GetStyleIdsByCoachId(int coachId);
        
        static std::vector<domain::Schedule> GetScheduleByGroup(int groupId);

        static bool AddSubscriptionToGroup(int groupId, int subscriptionId);
        static bool RemoveSubscriptionFromGroup(int groupId, int subscriptionId);
    };
}
