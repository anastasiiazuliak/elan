#pragma once
#include <vector>
#include "elan/domain/Coach.h"

namespace storage
{
    class CoachStorage
    {
    public:
        void AddCoach(const domain::Coach &coach);
        std::vector<domain::Coach> GetAllCoaches();
        void UpdateCoach (const domain::Coach);
        void DeleteCoach(int Id);
    };
}