#include "elan/services/MembershipService.h"
#include "elan/storage/Storages.h"

namespace service
{
    bool MembershipService::CreateMembership(int clientId, int groupId, int subscriptionId)
    {
        auto clientOpt = storages::Clients().GetById(clientId);
        auto groupOpt = storages::Groups().GetById(groupId);
        auto subOpt = storages::Subscriptions().GetById(subscriptionId);
        if (!clientOpt || !groupOpt || !subOpt) return false;

        auto client = clientOpt.value();
        auto group = groupOpt.value();

        if (client.GetCategory() != group.GetCategory())
            return false;

        bool subscriptionAllowed = false;
        for (int id : group.GetSubscriptionIds())
        {
            if (id == subscriptionId)
            {
                subscriptionAllowed = true;
                break;
            }
        }

        if (!subscriptionAllowed)
            return false;

        for (auto& existing : storages::Memberships().GetAll())
        {
            if (existing.GetClientId() == clientId &&
                existing.GetGroupId() == groupId &&
                existing.IsActive())
            {
                return false;
            }
        }

        auto sub = subOpt.value();

        domain::Membership m(
            clientId,
            groupId,
            subscriptionId,
            sub.GetDuration(),
            sub.GetNumberOfWorkouts()
        );

        storages::Memberships().Add(m);
        return true;
    }

    bool MembershipService::UseWorkout(int membershipId)
    {
        auto opt = storages::Memberships().GetById(membershipId);
        if (!opt) return false;

        auto m = opt.value();

        if (!m.IsActive()) return false;
        if (!m.UseWorkout()) return false;

        return storages::Memberships().Update(m.GetId(), m);
    }

    std::vector<domain::Membership> MembershipService::GetByClient(int clientId)
    {
        std::vector<domain::Membership> res;

        for (auto& m : storages::Memberships().GetAll())
        {
            if (m.GetClientId() == clientId)
                res.push_back(m);
        }

        return res;
    }

    std::vector<domain::Membership> MembershipService::GetByGroup(int groupId)
    {
        std::vector<domain::Membership> res;

        for (auto& m : storages::Memberships().GetAll())
        {
            if (m.GetGroupId() == groupId)
                res.push_back(m);
        }

        return res;
    }

    std::vector<domain::Membership> MembershipService::GetActiveByClient(int clientId)
    {
        std::vector<domain::Membership> res;

        for (auto& m : storages::Memberships().GetAll())
        {
            if (m.GetClientId() == clientId && m.IsActive())
                res.push_back(m);
        }

        return res;
    }

    std::vector<domain::Membership> MembershipService::GetActiveByGroup(int groupId)
    {
        std::vector<domain::Membership> res;

        for (auto& m : storages::Memberships().GetAll())
        {
            if (m.GetGroupId() == groupId && m.IsActive())
                res.push_back(m);
        }

        return res;
    }
}
