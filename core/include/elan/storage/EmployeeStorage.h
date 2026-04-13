#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Employee.h"

namespace storage
{
    class EmployeeStorage
    {
    public:
        void Add(const domain::Employee &employee);
        std::optional<domain::Employee> GetById(int id);
        std::vector<domain::Employee> GetAll();
        void Update(const domain::Employee &employee);
        void Delete(int Id);
    };
}
