#include "elan/domain/Group.h"

#include <iostream>

namespace domain
{
    Group::Group(int coachId, Style style, SkillLevel skillLevel)
    {
        this->coachId = coachId;
        this->style = style;
        this->skillLevel = skillLevel;
    }

    bool Group::AddClient(const Client &client)
    {
        if (countClients >= constants::MAX_CLIENTS)
            return false;

        for (int i = 0; i < countClients; i++)
        {
            if (clients[i].GetId() == client.GetId())
                return false;
        }

        clients[countClients++] = client;
        return true;
    }

    bool Group::RemoveClient(int clientId)
    {
        int index = -1;

        for (int i = 0; i < countClients; i++)
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

        for (int i = index; i < countClients - 1; i++)
        {
            clients[i] = clients[i + 1];
        }

        countClients--;

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

    int Group::GetCoachId()
    {
        return coachId;
    }

    //Удаліть
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

        std::cout << "Style: " << style.GetName() << "\n";

        std::cout << "Clients (" << countClients << "):\n";

        for (int i = 0; i < countClients; i++)
        {
            std::cout << "- "
                      << i + 1 << ". "
                      << clients[i].GetUsername()
                      << "\n";
        }

        std::cout << "\n";
    }
}
