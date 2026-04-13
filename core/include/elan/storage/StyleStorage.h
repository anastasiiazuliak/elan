#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Style.h"

namespace storage
{
    class StyleStorage
    {
    public:
        void Add(const domain::Style &style);
        std::optional<domain::Style> GetById(int id);
        std::vector<domain::Style> GetAll();
        void Update(const domain::Style &style);
        void Delete(int Id);
    };
}
