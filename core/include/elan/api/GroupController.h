#pragma once

#include "elan/domain/Group.h"
#include "elan/services/GroupService.h"

#include "crow.h"

namespace api
{
    class GroupController
    {
    public:
        static void RegisterRoutes(crow::SimpleApp &app);
    };
}