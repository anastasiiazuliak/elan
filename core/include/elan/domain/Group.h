#pragma once

#include "elan/domain/Client.h"
#include "elan/domain/Style.h"

namespace storage
{
    template <typename T>
    class Storage;
}

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
        int id;
        int coachId;
        Style style;
        SkillLevel skillLevel;
        Client clients[constants::MAX_CLIENTS];

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        int GetId() const;
        int GetCoachId();
    };
}