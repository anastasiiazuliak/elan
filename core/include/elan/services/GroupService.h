#pragma once

#include <vector>

#include "elan/storage/Storage.h"
#include "elan/domain/Group.h"

namespace service
{
    class GroupService
    {
        static storage::Storage<domain::Group> groups;
        static storage::Storage<domain::Client> clients;
    public:
        static std::vector<domain::Group> GetGroupsByCoachId(int id);
        
        static bool AddClientToGroup(int groupId, int clientId);
        static bool RemoveClientFromGroup(int groupId, int clientId);
    };
}
