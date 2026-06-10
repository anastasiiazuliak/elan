#include "elan/services/GroupService.h"

namespace service
{
    std::vector<domain::Group> GroupService::GetGroupsByCoachId(int id)
    {
        std::vector<domain::Group> allGroups = storages::Groups().GetAll();
        std::vector<domain::Group> coachGroups;

        for (const auto &g : allGroups)
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
        auto groupOpt = storages::Groups().GetById(groupId);
        auto clientOpt = storages::Clients().GetById(clientId);

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

        return storages::Groups().Update(group.GetId(), group);
    }

    bool GroupService::RemoveClientFromGroup(int groupId, int clientId)
    {
        auto groupOpt = storages::Groups().GetById(groupId);

        if (!groupOpt.has_value())
        {
            return false;
        }

        auto group = groupOpt.value();

        if (!group.RemoveClient(clientId))
        {
            return false;
        }

        return storages::Groups().Update(group.GetId(), group);
    }

    std::vector<domain::Schedule> GroupService::GetScheduleByGroup(int groupId)
    {
        std::vector<domain::Schedule> result;

        auto locationsAll = storages::Locations().GetAll();

        for (const auto& loc : locationsAll)
        {
            auto part = service::LocationService::GetScheduleByGroup(
                loc.GetId(),
                groupId
            );

            result.insert(result.end(), part.begin(), part.end());
        }

        return result;
    }
}