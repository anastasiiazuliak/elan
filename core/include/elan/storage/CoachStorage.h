#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Coach.h"

namespace storage
{
    class CoachStorage
    {
    public:
        void Add(const domain::Coach &coach);
        std::optional<domain::Coach> GetById(int id);
        std::vector<domain::Coach> GetAll();
        void Update(const domain::Coach &coach);
        void Delete(int Id);
    };
}
