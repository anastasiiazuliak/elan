#pragma once

#include "Style.h"
#include "Client.h"

namespace domain
{
    enum class SkillLevel
    {
        Beginner, 
        Intermediate, 
        Advanced
    };

    class Group
    {
        int Id;
        int CoachId;
        Style Style;
        SkillLevel SkillLevel;
        Client Clients[25];
    };
}