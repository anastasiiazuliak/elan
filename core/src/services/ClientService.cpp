#include "elan/services/ClientService.h"

storage::Storage<domain::Subscription> &subscriptions(
    "../data/subscriptions.bin",
    "../data/subscriptions_id.bin");

storage::Storage<domain::Client> &clients(
    "../data/clients.bin",
    "../data/clients_id.bin");

namespace service
{
    bool ClientService::ChangeClientSubscription(int clientId, int subscriptionId)
    {
        auto clientOpt = clients.GetById(clientId);
        auto subOpt = subscriptions.GetById(subscriptionId);

        if (!clientOpt.has_value() || !subOpt.has_value())
        {
            return false;
        }

        auto client = *clientOpt;

        client.ChangeSubscription(subscriptionId);

        return clients.Update(client);
    }
}