#pragma once

#include <crow.h>

namespace api
{
    class AuthController
    {
    public:
        static void RegisterRoutes(crow::SimpleApp& app);
    };
}