#include "elan/services/ClientService.h"

namespace service
{
    storage::Storage<domain::Subscription> ClientService::subscriptions(
        constants::SUBSCRIPTIONS_FILE,
        constants::SUBSCRIPTIONS_ID_FILE);

    storage::Storage<domain::Client> ClientService::clients(
        constants::CLIENTS_FILE,
        constants::CLIENTS_ID_FILE);

    bool ClientService::ChangeClientSubscription(int clientId, int subscriptionId)
    {
        auto clientOpt = clients.GetById(clientId);

        if (!clientOpt.has_value() || !subscriptions.GetById(subscriptionId).has_value())
        {
            return false;
        }

        auto client = *clientOpt;

        client.ChangeSubscription(subscriptionId);

        return clients.Update(client.GetId(), client);
    }
}