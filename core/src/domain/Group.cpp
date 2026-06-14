#include "elan/domain/Group.h"

#include <iostream>
#include <cstring>

namespace domain
{
    Group::Group(const char *name, int coachId, int styleId, SkillLevel skillLevel, common::Category category)
    {
        strcpy(this->name, name);
        this->coachId = coachId;
        this->styleId = styleId;
        this->skillLevel = skillLevel;
        this->category = category;

        subscriptionsCount = 0;
    }

    bool Group::AddSubscription(int subscriptionId)
    {
        if (subscriptionsCount >= constants::MAX_SUBSCRIPTIONS)
            return false;

        for (int i = 0; i < subscriptionsCount; i++)
        {
            if (subscriptionIds[i] == subscriptionId)
                return false;
        }

        subscriptionIds[subscriptionsCount++] = subscriptionId;
        return true;
    }

    bool Group::RemoveSubscription(int subscriptionId)
    {
        int index = -1;

        for (int i = 0; i < subscriptionsCount; i++)
        {
            if (subscriptionIds[i] == subscriptionId)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            return false;

        for (int i = index; i < subscriptionsCount - 1; i++)
        {
            subscriptionIds[i] = subscriptionIds[i + 1];
        }

        subscriptionsCount--;
        return true;
    }

    void Group::SetId(int id)
    {
        this->id = id;
    }

    int Group::GetId() const
    {
        return id;
    }

    const char *Group::GetName() const
    {
        return name;
    }

    int Group::GetCoachId() const
    {
        return coachId;
    }

    SkillLevel Group::GetSkillLevel() const
    {
        return skillLevel;
    }

    common::Category Group::GetCategory() const
    {
        return category;
    }

    int Group::GetStyleId() const
    {
        return styleId;
    }

    int Group::GetSubscriptionCount() const
    {
        return subscriptionsCount;
    }

    std::vector<int> Group::GetSubscriptionIds() const
    {
        std::vector<int> result;

        for (int i = 0; i < subscriptionsCount; i++)
        {
            result.push_back(subscriptionIds[i]);
        }

        return result;
    }

    void Group::PrintGroup()
    {
        std::cout << "========== GROUP ==========\n";
        std::cout << "Group ID: " << id << "\n";
        std::cout << "Coach ID: " << coachId << "\n";
        std::cout << "Style ID: " << styleId << "\n";

        switch (category)
        {
        case common::Category::Age_3_5:
            std::cout << "3-5 years";
            break;
        case common::Category::Age_5_plus:
            std::cout << "5+ years";
            break;
        case common::Category::Age_6_plus:
            std::cout << "6+ years";
            break;
        case common::Category::Age_7_plus:
            std::cout << "7+ years";
            break;
        case common::Category::Age_10_12:
            std::cout << "10-12 years";
            break;
        case common::Category::Age_14_plus:
            std::cout << "14+ years";
            break;
        case common::Category::Age_16_plus:
            std::cout << "16+ years";
            break;
        }

        std::cout << "Subscriptions (" << subscriptionsCount << "):\n";
        for (int i = 0; i < subscriptionsCount; i++)
        {
            std::cout << "- Subscription ID: " << subscriptionIds[i] << "\n";
        }

        std::cout << "\n";
    }
}
