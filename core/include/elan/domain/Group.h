#pragma once

#include "elan/common/constants.h"

#include <vector>

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
        char name[constants::NAME_LENGTH];
        int coachId;
        int styleId;
        SkillLevel skillLevel;
        int clientIds[constants::MAX_CLIENTS];
        int clientsCount = 0;

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        Group() = default;
        Group(const char *name, int coachId, int styleId, SkillLevel skillLevel);

        int GetId() const;
        const char *GetName() const;
        int GetCoachId() const;
        SkillLevel GetSkillLevel() const;
        int GetStyleId() const;

        int GetClientCount() const;
        std::vector<int> GetClientIds() const;

        bool AddClient(int clientId);
        bool RemoveClient(int clientId);

        void PrintGroup();
    };
}