#include "elan/services/GroupService.h"

storage::Storage<domain::Group> groups(
    "../data/groups.bin",
    "../data/groups_id.bin");

storage::Storage<domain::Client> &clients(
    "../data/clients.bin",
    "../data/clients_id.bin");

namespace service
{
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

        if (!group.has_value() || !client.has_value())
        {
            return false;
        }

        auto group = groupOpt.value();   // копія
        auto client = clientOpt.value(); // копія

        if (!group.AddClient(client))
        {
            return false;
        }

        return groups.Update(group);
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

        return groups.Update(group);
    }
}