#pragma once

#include "elan/storage/Storage.h"
#include "elan/domain/Coach.h"
#include "elan/domain/Style.h"

namespace service
{
    class CoachService
    {
        static storage::Storage<domain::Coach> coaches;
        static storage::Storage<domain::Style> styles;
    public:
        bool AddStyleToCoach(int coachId, int styleId);
        bool RemoveStyleFromCoach(int coachId, int styleId);
    };
}