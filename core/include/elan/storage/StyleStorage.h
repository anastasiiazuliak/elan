#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Style.h"

namespace storage
{
    class StyleStorage
    {
    public:
        void Add(domain::Style &style);
        std::optional<domain::Style> GetById(int id);
        std::vector<domain::Style> GetAll();
        bool Update(const domain::Style &style);
        bool Delete(int id);
    };
}
