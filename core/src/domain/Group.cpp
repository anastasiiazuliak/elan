#include "elan/domain/Group.h"

#include <iostream>

namespace domain
{
    Group::Group(int coachId, int styleId, SkillLevel skillLevel)
    {
        this->coachId = coachId;
        this->styleId = styleId;
        this->skillLevel = skillLevel;
    }

    bool Group::AddClient(const Client &client)
    {
        if (clientsCount >= constants::MAX_CLIENTS)
            return false;

        for (int i = 0; i < clientsCount; i++)
        {
            if (clients[i].GetId() == client.GetId())
                return false;
        }

        clients[clientsCount++] = client;
        return true;
    }

    bool Group::RemoveClient(int clientId)
    {
        int index = -1;

        for (int i = 0; i < clientsCount; i++)
        {
            if (clients[i].GetId() == clientId)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            return false;
        }

        for (int i = index; i < clientsCount - 1; i++)
        {
            clients[i] = clients[i + 1];
        }

        clientsCount--;

        return true;
    }

    void Group::SetId(int id)
    {
        this->id = id;
    }

    int Group::GetId() const
    {
        return id;
    }

    int Group::GetCoachId() const
    {
        return coachId;
    }

    SkillLevel Group::GetSkillLevel() const
    {
        return skillLevel;
    }

    int Group::GetStyleId() const
    {
        return styleId;
    }

    int Group::GetClientCount() const
    {
        return clientsCount;
    }

    // Удаліть
    void Group::PrintGroup()
    {
        std::cout << "========== GROUP ==========\n";

        std::cout << "Group ID: " << id << "\n";
        std::cout << "Coach ID: " << coachId << "\n";

        std::cout << "Skill level: ";

        switch (skillLevel)
        {
        case SkillLevel::Beginner:
            std::cout << "Beginner";
            break;
        case SkillLevel::Intermediate:
            std::cout << "Intermediate";
            break;
        case SkillLevel::Advanced:
            std::cout << "Advanced";
            break;
        }

        std::cout << "\n";

        std::cout << "Style: " << styleId << "\n";

        std::cout << "Clients (" << clientsCount << "):\n";

        for (int i = 0; i < clientsCount; i++)
        {
            std::cout << "- "
                      << i + 1 << ". "
                      << clients[i].GetUsername()
                      << "\n";
        }

        std::cout << "\n";
    }
}
