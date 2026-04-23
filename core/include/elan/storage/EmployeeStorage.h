#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Employee.h"

namespace storage
{
    class EmployeeStorage
    {
    public:
        void Add(domain::Employee &employee);
        std::optional<domain::Employee> GetById(int id);
        std::vector<domain::Employee> GetAll();
        bool Update(const domain::Employee &employee);
        bool Delete(int id);
    };
}
