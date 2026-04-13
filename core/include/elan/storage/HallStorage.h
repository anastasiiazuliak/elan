#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Hall.h"

namespace storage
{
    class HallStorage
    {
    public:
        void Add(const domain::Hall &hall);
        std::optional<domain::Hall> GetById(int id);
        std::vector<domain::Hall> GetAll();
        void Update (const domain::Hall &hall);
        void Delete(int Id);
    };
}
