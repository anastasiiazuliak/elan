#pragma once

#include <crow.h>

#include "elan/domain/Coach.h"

namespace api
{
    class CoachController
    {
    public:
        static void RegisterRoutes(crow::SimpleApp& app);
    };
}