#pragma once

#include "elan/domain/Client.h"

#include "crow.h"

namespace api
{
    class ClientController
    {
    public:
        static void RegisterRoutes(crow::SimpleApp& app);
    };
}