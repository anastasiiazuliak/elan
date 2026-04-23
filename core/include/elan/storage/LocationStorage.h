#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Location.h"

namespace storage
{
    class LocationStorage
    {
    public:
        void Add(domain::Location &location);
        std::optional<domain::Location> GetById(int id);
        std::vector<domain::Location> GetAll();
        bool Update(const domain::Location &location);
        bool Delete(int id);
    };
}
