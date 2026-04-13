#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Subscription.h"

namespace storage
{
    class SubscriptionStorage
    {
    public:
        void Add(const domain::Subscription &subscription);
        std::optional<domain::Subscription> GetById(int id);
        std::vector<domain::Subscription> GetAll();
        void Update(const domain::Subscription &subscription);
        void Delete(int Id);
    };
}
