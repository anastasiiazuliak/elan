#pragma once

#include "elan/domain/Style.h"

#include "crow.h"

namespace api
{
    class StyleController
    {
    public:
        static void RegisterRoutes(crow::SimpleApp& app);
    };
}
