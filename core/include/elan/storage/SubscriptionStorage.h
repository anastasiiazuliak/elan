#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Subscription.h"

namespace storage
{
    class SubscriptionStorage
    {
    public:
        void Add(domain::Subscription &subscription);
        std::optional<domain::Subscription> GetById(int id);
        std::vector<domain::Subscription> GetAll();
        bool Update(const domain::Subscription &subscription);
        bool Delete(int id);
    };
}
