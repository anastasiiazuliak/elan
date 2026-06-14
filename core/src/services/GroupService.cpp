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
    }

    std::vector<int> GroupService::GetStyleIdsByCoachId(int coachId)
    {
        auto coachOpt = storages::Coaches().GetById(coachId);

        if (!coachOpt.has_value())
        {
            return {};
        }

        auto coach = coachOpt.value();
        const int *styleIds = coach.GetStyleIds();
        std::vector<int> result;

        for (int i = 0; i < coach.GetStylesCount(); i++)
        {
            result.push_back(styleIds[i]);
        }

        return result;
    }
    
    bool GroupService::AddSubscriptionToGroup(int groupId, int subscriptionId)
    {
        auto groupOpt = storages::Groups().GetById(groupId);
        auto subscriptionOpt = storages::Subscriptions().GetById(subscriptionId);

        if (!groupOpt.has_value() || !subscriptionOpt.has_value())
        {
            return false;
        }

        auto group = groupOpt.value();

        if (!group.AddSubscription(subscriptionId))
        {
            return false;
        }

        return storages::Groups().Update(group.GetId(), group);
    }

    bool GroupService::RemoveSubscriptionFromGroup(int groupId, int subscriptionId)
    {
        auto groupOpt = storages::Groups().GetById(groupId);

        if (!groupOpt.has_value())
        {
            return false;
        }

        auto group = groupOpt.value();

        if (!group.RemoveSubscription(subscriptionId))
        {
            return false;
        }

        return storages::Groups().Update(group.GetId(), group);
    }

    std::vector<domain::Schedule> GroupService::GetScheduleByGroup(int groupId)
    {
        std::vector<domain::Schedule> result;

        auto locationsAll = storages::Locations().GetAll();

        for (const auto &loc : locationsAll)
        {
            auto part = service::LocationService::GetScheduleByGroup(
                loc.GetId(),
                groupId);

            result.insert(result.end(), part.begin(), part.end());
        }

        return result;
    }
}
