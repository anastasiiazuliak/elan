#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Group.h"

namespace storage
{
    class GroupStorage
    {
    public:
        void Add(const domain::Group &group);
        std::optional<domain::Group> GetById(int id);
        std::vector<domain::Group> GetAll();
        void Update(const domain::Group &group);
        void Delete(int Id);
    };
}
