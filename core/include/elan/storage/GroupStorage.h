#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Group.h"

namespace storage
{
    class GroupStorage
    {
    public:
        void Add(domain::Group &group);
        std::optional<domain::Group> GetById(int id);
        std::vector<domain::Group> GetAll();
        bool Update(const domain::Group &group);
        bool Delete(int id);
    };
}
