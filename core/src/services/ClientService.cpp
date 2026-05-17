#include "elan/services/ClientService.h"

namespace service
{
    storage::Storage<domain::Subscription> ClientService::subscriptions(
        "../data/subscriptions.bin",
        "../data/subscriptions_id.bin");

    storage::Storage<domain::Client> ClientService::clients(
        "../data/clients.bin",
        "../data/clients_id.bin");

    bool ClientService::ChangeClientSubscription(int clientId, int subscriptionId)
    {
        auto clientOpt = clients.GetById(clientId);

        if (!clientOpt.has_value() || !subscriptions.GetById(subscriptionId).has_value())
        {
            return false;
        }

        auto client = *clientOpt;

        client.ChangeSubscription(subscriptionId);

        return clients.Update(client);
    }
}