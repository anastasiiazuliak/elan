#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Location.h"

namespace storage
{
    class LocationStorage
    {
    public:
        void Add(const domain::Location &location);
        std::optional<domain::Location> GetById(int id);
        std::vector<domain::Location> GetAll();
        void Update(const domain::Location &location);
        void Delete(int Id);
    };
}
