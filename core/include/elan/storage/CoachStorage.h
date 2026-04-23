#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Coach.h"

namespace storage
{
    class CoachStorage
    {
    public:
        void Add(domain::Coach &coach);
        std::optional<domain::Coach> GetById(int id);
        std::vector<domain::Coach> GetAll();
        bool Update(const domain::Coach &coach);
        bool Delete(int id);
    };
}
