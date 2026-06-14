#pragma once

#include "crow.h"

namespace api
{
    class MembershipController
    {
    public:
        static void RegisterRoutes(crow::SimpleApp &app);
    };
}