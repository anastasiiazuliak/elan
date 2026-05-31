#include "elan/services/GroupService.h"

namespace service
{
    storage::Storage<domain::Group> GroupService::groups(
        constants::GROUPS_FILE,
        constants::GROUPS_ID_FILE);

    storage::Storage<domain::Client> GroupService::clients(
        constants::CLIENTS_FILE,
        constants::CLIENTS_ID_FILE);

    storage::Storage<domain::Location> GroupService::locations(
        constants::LOCATIONS_FILE,
        constants::LOCATIONS_ID_FILE);

    std::vector<domain::Group> GroupService::GetGroupsByCoachId(int id)
    {
        std::vector<domain::Group> allGroups = groups.GetAll();
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

    std::vector<domain::Schedule> GroupService::GetScheduleByGroup(int groupId)
    {
        std::vector<domain::Schedule> result;

        auto locationsAll = locations.GetAll();

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