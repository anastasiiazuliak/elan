#pragma once

#include <crow.h>

#include "elan/domain/Employee.h"

namespace api
{
    class EmployeeController
    {
    public:
        static void RegisterRoutes(crow::SimpleApp& app);
    };
}