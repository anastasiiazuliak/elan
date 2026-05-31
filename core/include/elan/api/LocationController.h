#pragma once

#include <crow.h>

#include "elan/storage/Storage.h"
#include "elan/domain/Location.h"

namespace api
{
    class LocationController
    {
    private:
        static storage::Storage<domain::Location> locations;

    public:
        static void RegisterRoutes(crow::SimpleApp &app);
    };
}