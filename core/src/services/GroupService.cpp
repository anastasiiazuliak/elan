#include "elan/services/GroupService.h"

namespace service
{
    storage::Storage<domain::Group> GroupService::groups(
        "../data/groups.bin",
        "../data/groups_id.bin");

    storage::Storage<domain::Client> GroupService::clients(
        "../data/clients.bin",
        "../data/clients_id.bin");

    std::vector<domain::Group> GroupService::GetGroupsByCoachId(int id)
    {
        std::vector<domain::Group> allGroups = groups.GetAll();
        std::vector<domain::Group> coachGroups;

        for (auto g : allGroups)
        {
            if (g.GetCoachId() == id)
            {
                coachGroups.push_back(g);
            }
        }

        return coachGroups;
    };

    bool GroupService::AddClientToGroup(int groupId, int clientId)
    {
        auto groupOpt = groups.GetById(groupId);
        auto clientOpt = clients.GetById(clientId);

        if (!groupOpt.has_value() || !clientOpt.has_value())
        {
            return false;
        }

        auto group = groupOpt.value();   // копія
        auto client = clientOpt.value(); // копія

        if (!group.AddClient(client))
        {
            return false;
        }

        return groups.Update(group.GetId(), group);
    }

    bool GroupService::RemoveClientFromGroup(int groupId, int clientId)
    {
        auto groupOpt = groups.GetById(groupId);

        if (!groupOpt.has_value())
        {
            return false;
        }

        auto group = groupOpt.value();

        if (!group.RemoveClient(clientId))
        {
            return false;
        }

        return groups.Update(group.GetId(), group);
    }
}