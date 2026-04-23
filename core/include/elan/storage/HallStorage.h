#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Hall.h"

namespace storage
{
    class HallStorage
    {
    public:
        void Add(domain::Hall &hall);
        std::optional<domain::Hall> GetById(int id);
        std::vector<domain::Hall> GetAll();
        bool Update (const domain::Hall &hall);
        bool Delete(int id);
    };
}
