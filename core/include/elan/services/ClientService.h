#pragma once

#include "elan/storage/Storage.h"
#include "elan/domain/Client.h"
#include "elan/domain/Subscription.h"

namespace service
{
    class ClientService
    {
    public:
        bool ChangeClientSubscription(int clientId, int subscriptionId);
    };
}