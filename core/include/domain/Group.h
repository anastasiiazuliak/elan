#pragma once

#include "Style.h"

namespace domain
{
    struct Group
    {
        int Id;
        int CoachId;
        Style Style;
        char *SkillLevel;
        // Client* Clients[];
    };
}