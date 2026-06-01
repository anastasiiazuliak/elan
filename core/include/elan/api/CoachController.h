#pragma once

#include <crow.h>

#include "elan/storage/Storage.h"
#include "elan/domain/Coach.h"

namespace api
{
    class CoachController
    {
        static storage::Storage<domain::Coach> coaches;

    public:
        static void RegisterRoutes(crow::SimpleApp& app);
    };
}