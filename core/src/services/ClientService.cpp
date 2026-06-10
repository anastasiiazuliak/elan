#include "elan/services/ClientService.h"


namespace service
{
    bool ClientService::ChangeClientSubscription(int clientId, int subscriptionId)
    {
        auto clientOpt = storages::Clients().GetById(clientId);

        if (!clientOpt.has_value() || !storages::Subscriptions().GetById(subscriptionId).has_value())
        {
            return false;
        }

        auto client = *clientOpt;

        client.ChangeSubscription(subscriptionId);

        return storages::Clients().Update(client.GetId(), client);
    }
}