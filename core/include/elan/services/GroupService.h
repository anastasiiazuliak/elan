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
        
        static bool AddClientToGroup(int groupId, int clientId);
        static bool RemoveClientFromGroup(int groupId, int clientId);
        static std::vector<domain::Client> GetClientsByGroup(int groupId);

        static std::vector<domain::Schedule> GetScheduleByGroup(int groupId);
    };
}
