#pragma once

#include <vector>

#include "elan/storage/Storage.h"
#include "elan/domain/Group.h"
#include "elan/services/LocationService.h"

namespace service
{
    class GroupService
    {
        static storage::Storage<domain::Group> groups;
        static storage::Storage<domain::Client> clients;
        static storage::Storage<domain::Location> locations;
    public:
        static std::vector<domain::Group> GetGroupsByCoachId(int id);
        
        static bool AddClientToGroup(int groupId, int clientId);
        static bool RemoveClientFromGroup(int groupId, int clientId);

        static std::vector<domain::Schedule> GroupService::GetScheduleByGroup(int groupId);
    };
}
