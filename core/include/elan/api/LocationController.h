#pragma once

#include <crow.h>

#include "elan/domain/Location.h"

namespace api
{
    class LocationController
    {
    public:
        static void RegisterRoutes(crow::SimpleApp &app);
    };
}