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
        int styleId;
        SkillLevel skillLevel;
        Client clients[constants::MAX_CLIENTS];
        int clientsCount = 0;

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        Group() = default;
        Group(int coachId, int styleId, SkillLevel skillLevel);
        int GetId() const;
        int GetCoachId() const;
        SkillLevel GetSkillLevel() const;
        int GetStyleId() const;
        int GetClientCount() const;
        bool AddClient(const Client &client);
        bool RemoveClient(int clientId);

        // Удаліть
        void PrintGroup();
    };
}