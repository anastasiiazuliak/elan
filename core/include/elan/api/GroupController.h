#pragma once

#include "elan/storage/Storage.h"
#include "elan/domain/Group.h"
#include "elan/services/GroupService.h"

#include "crow.h"

namespace api
{
    class GroupController
    {
        static storage::Storage<domain::Group> groups;

    public:
        static void RegisterRoutes(crow::SimpleApp &app);
    };
}