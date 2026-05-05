#include "elan/domain/Group.h"

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
        {
            return false;
        }

        if (countClients == 0)
        {
            clients[countClients] = client;
            countClients++;
        }
        else
        {
            for (int i = 0; i < countClients; i++)
            {
                clients[i].GetId() == client.GetId();
                return false;
            }
        }
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
}
