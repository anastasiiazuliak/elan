#pragma once

#include <vector>

#include "elan/storage/Storage.h"
#include "elan/domain/Group.h"

namespace service
{
    class GroupService
    {
        
    public:
        std::vector<domain::Group> GetGroupsByCoachId(int id);
        
        bool AddClientToGroup(int groupId, int clientId);
        bool RemoveClientFromGroup(int groupId, int clientId);
    };
}
