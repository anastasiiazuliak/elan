#pragma once

#include "elan/storage/Storages.h"
#include "elan/domain/Coach.h"
#include "elan/domain/Style.h"

namespace service
{
    class CoachService
    {
    public:
        static bool AddStyleToCoach(int coachId, int styleId);
        static bool RemoveStyleFromCoach(int coachId, int styleId);
    };
}