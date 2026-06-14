#include "elan/domain/Membership.h"
#include "elan/common/Date.h"

namespace domain
{
    Membership::Membership(int clientId, int groupId, int subscriptionId, int duration, int numberOfWorkouts)
    {
        this->clientId = clientId;
        this->groupId = groupId;
        this->subscriptionId = subscriptionId;

        common::Date start = common::Today();
        common::Date end = common::AddDays(start, duration);

        this->startDate = start;
        this->endDate = end;

        this->remainingWorkouts = numberOfWorkouts;
        this->completedWorkouts = 0;
    }

    void Membership::SetId(int id)
    {
        this->id = id;
    }

    int Membership::GetId() const
    {
        return id;
    }

    int Membership::GetClientId() const
    {
        return clientId;
    }

    int Membership::GetGroupId() const
    {
        return groupId;
    }

    int Membership::GetSubscriptionId() const
    {
        return subscriptionId;
    }

    common::Date Membership::GetStartDate() const
    {
        return startDate;
    }

    common::Date Membership::GetEndDate() const
    {
        return endDate;
    }

    int Membership::GetRemainingWorkouts() const
    {
        return remainingWorkouts;
    }

    int Membership::GetCompletedWorkouts() const
    {
        return completedWorkouts;
    }

    bool Membership::UseWorkout()
    {
        if (remainingWorkouts <= 0)
        {
            return false;
        }

        remainingWorkouts--;
        completedWorkouts++;

        return true;
    }

    bool Membership::IsActive() const
    {
        common::Date today = common::Today();

        bool notExpired =
            (today.year < endDate.year) ||
            (today.year == endDate.year && today.month < endDate.month) ||
            (today.year == endDate.year && today.month == endDate.month && today.day <= endDate.day);

        return notExpired && remainingWorkouts > 0;
    }
}