#include "elan/services/CoachService.h"

namespace service
{
    bool CoachService::AddStyleToCoach(int coachId, int styleId)
    {
        auto coachOpt = storages::Coaches().GetById(coachId);
        auto styleOpt = storages::Styles().GetById(styleId);

        if (!coachOpt.has_value() || !styleOpt.has_value())
        {
            return false;
        }

        auto coach = *coachOpt;

        if (!coach.AddStyle(styleId))
        {
            return false;
        }

        return storages::Coaches().Update(coach.GetId(), coach);
    }

    bool CoachService::RemoveStyleFromCoach(int coachId, int styleId)
    {
        auto coachOpt = storages::Coaches().GetById(coachId);

        if (!coachOpt.has_value())
        {
            return false;
        }

        auto coach = *coachOpt;

        if (!coach.RemoveStyle(styleId))
        {
            return false;
        }

        return storages::Coaches().Update(coach.GetId(), coach);
    }
}