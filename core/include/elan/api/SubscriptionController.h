#pragma once

#include "elan/domain/Subscription.h"

#include "crow.h"

namespace api
{
    class SubscriptionController
    {
    public:
        static void RegisterRoutes(crow::SimpleApp& app);
    };
}
