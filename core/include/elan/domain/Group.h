#pragma once

#include "elan/common/constants.h"
#include "elan/common/Category.h"

#include <vector>

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    enum class SkillLevel
    {
        Beginner,
        Intermediate,
        Advanced
    };

    class Group
    {
        int id;
        char name[constants::NAME_LENGTH];
        int coachId;
        int styleId;
        SkillLevel skillLevel;
        common::Category category;


        int subscriptionIds[constants::MAX_SUBSCRIPTIONS];
        int subscriptionsCount = 0;

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        Group() = default;
        Group(const char *name, int coachId, int styleId, SkillLevel skillLevel, common::Category category);

        int GetId() const;
        const char *GetName() const;
        int GetCoachId() const;
        SkillLevel GetSkillLevel() const;
        int GetStyleId() const;
        common::Category GetCategory() const;

        int GetSubscriptionCount() const;
        std::vector<int> GetSubscriptionIds() const;

        bool AddSubscription(int subscriptionId);
        bool RemoveSubscription(int subscriptionId);

        void PrintGroup();
    };
}
