#include "elan/domain/Group.h"

#include <iostream>
#include <cstring>

namespace domain
{
    Group::Group(const char *name, int coachId, int styleId, SkillLevel skillLevel)
    {
        strcpy(this->name, name);
        this->coachId = coachId;
        this->styleId = styleId;
        this->skillLevel = skillLevel;
    }

    bool Group::AddClient(int clientId)
    {
        if (clientsCount >= constants::MAX_CLIENTS)
            return false;

        for (int i = 0; i < clientsCount; i++)
        {
            if (clientIds[i] == clientId)
                return false;
        }

        clientIds[clientsCount++] = clientId;
        return true;
    }

    bool Group::RemoveClient(int clientId)
    {
        int index = -1;

        for (int i = 0; i < clientsCount; i++)
        {
            if (clientIds[i] == clientId)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            return false;

        for (int i = index; i < clientsCount - 1; i++)
        {
            clientIds[i] = clientIds[i + 1];
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

    const char *Group::GetName() const
    {
        return name;
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

    std::vector<int> Group::GetClientIds() const
    {
        std::vector<int> result;

        for (int i = 0; i < clientsCount; i++)
        {
            result.push_back(clientIds[i]);
        }

        return result;
    }

    void Group::PrintGroup()
    {
        std::cout << "========== GROUP ==========\n";
        std::cout << "Group ID: " << id << "\n";
        std::cout << "Coach ID: " << coachId << "\n";
        std::cout << "Style ID: " << styleId << "\n";
        std::cout << "Clients (" << clientsCount << "):\n";

        for (int i = 0; i < clientsCount; i++)
        {
            std::cout << "- Client ID: " << clientIds[i] << "\n";
        }

        std::cout << "\n";
    }
}