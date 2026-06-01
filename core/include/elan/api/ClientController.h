#pragma once

#include "elan/storage/Storage.h"
#include "elan/domain/Client.h"

#include "crow.h"

namespace api
{
    class ClientController
    {
        static storage::Storage<domain::Client> clients;

    public:
        static void RegisterRoutes(crow::SimpleApp& app);
    };
}