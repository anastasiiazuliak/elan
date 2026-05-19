#pragma once

#include "elan/storage/Storage.h"
#include "elan/domain/Style.h"

#include "crow.h"

namespace api
{
    class StyleController
    {
        static storage::Storage<domain::Style> styles;
    public:
        static void RegisterRoutes(crow::SimpleApp& app);
    };
}