#pragma once

#include <crow.h>

#include "elan/storage/Storage.h"
#include "elan/domain/Employee.h"

namespace api
{
    class EmployeeController
    {
        static storage::Storage<domain::Employee> employees;

    public:
        static void RegisterRoutes(crow::SimpleApp& app);
    };
}