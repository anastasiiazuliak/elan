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
        int countClients = 0;

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        Group() = default;
        Group(int coachId, Style style, SkillLevel skillLevel);
        int GetId() const;
        int GetCoachId();
        bool AddClient(const Client &client);
        bool RemoveClient(int clientId);

        // Удаліть
        void PrintGroup();
    };
}