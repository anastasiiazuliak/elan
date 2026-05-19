#pragma once

#include "elan/storage/Storage.h"
#include "elan/domain/Subscription.h"

#include "crow.h"

namespace api
{
    class SubscriptionController
    {
        static storage::Storage<domain::Subscription> subscriptions;
    public:
        static void RegisterRoutes(crow::SimpleApp& app);
    };
}