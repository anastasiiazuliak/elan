#include "elan/services/CoachService.h"

namespace service
{
    storage::Storage<domain::Coach> CoachService::coaches(
        constants::COACHES_FILE,
        constants::COACHES_ID_FILE);

    storage::Storage<domain::Style> CoachService::styles(
        constants::STYLES_FILE,
        constants::STYLES_ID_FILE);

    bool CoachService::AddStyleToCoach(int coachId, int styleId)
    {
        auto coachOpt = coaches.GetById(coachId);
        auto styleOpt = styles.GetById(styleId);

        if (!coachOpt.has_value() || !styleOpt.has_value())
        {
            return false;
        }

        auto coach = *coachOpt;
        auto style = *styleOpt;

        if (!coach.AddStyle(style))
        {
            return false;
        }

        return coaches.Update(coach.GetId(), coach);
    }

    bool CoachService::RemoveStyleFromCoach(int coachId, int styleId)
    {
        auto coachOpt = coaches.GetById(coachId);

        if (!coachOpt.has_value())
        {
            return false;
        }

        auto coach = *coachOpt;

        if (!coach.RemoveStyle(styleId))
        {
            return false;
        }

        return coaches.Update(coach.GetId(), coach);
    }
}