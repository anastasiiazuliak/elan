#pragma once

#include "elan/common/Date.h"

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    class Membership
    {
        int id;

        int clientId;
        int groupId;
        int subscriptionId;

        common::Date startDate;
        common::Date endDate;

        int remainingWorkouts;
        int completedWorkouts;

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        Membership() = default;

        Membership(int clientId, int groupId, int subscriptionId, int duration, int numberOfWorkouts);

        int GetId() const;

        int GetClientId() const;
        int GetGroupId() const;
        int GetSubscriptionId() const;

        common::Date GetStartDate() const;
        common::Date GetEndDate() const;

        int GetRemainingWorkouts() const;
        int GetCompletedWorkouts() const;

        bool UseWorkout();
        bool IsActive() const;
    };
}
