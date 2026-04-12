#pragma once
#include <vector>
#include "elan/domain/Employee.h"

namespace storage
{
    class EmployeeStorage
    {
    public:
        void AddEmployee(const domain::Employee &employee);
        std::vector<domain::Employee> GetAllEmployees();
        void UpdateEmployee (const domain::Employee);
        void DeleteEmployee(int Id);
    };
}