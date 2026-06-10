#pragma once

#include "elan/storage/Storages.h"
#include "elan/domain/Client.h"
#include "elan/domain/Subscription.h"

namespace service
{
    class ClientService
    {
    public:
        static bool ChangeClientSubscription(int clientId, int subscriptionId);
    };
}