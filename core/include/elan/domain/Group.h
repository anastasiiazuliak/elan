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
        int Id;
        int CoachId;
        Style Style;
        SkillLevel SkillLevel;
        Client Clients[25];

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        int GetId() const;
    };
}