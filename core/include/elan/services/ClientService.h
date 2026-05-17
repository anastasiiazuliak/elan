#pragma once

#include "elan/storage/Storage.h"
#include "elan/domain/Client.h"
#include "elan/domain/Subscription.h"

namespace service
{
    class ClientService
    {
        static storage::Storage<domain::Subscription> subscriptions;
        static storage::Storage<domain::Client> clients;

    public:
        bool ChangeClientSubscription(int clientId, int subscriptionId);
    };
}