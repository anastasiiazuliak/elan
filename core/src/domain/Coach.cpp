#include "elan/domain/Coach.h"

#include <cstring>

namespace domain
{
        Coach::Coach(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone,   const char *description, domain::Style inputStyles[constants::MAX_STYLES], const char* password, const char *username) : Person(firstName, lastName, patronymic, birthDate, phone, password, username)
        {
            strcpy(this->description, description);

            stylesCount = 0;
            for (int i = 0; i < constants::MAX_STYLES; i++)
            {
                styles[stylesCount++] = inputStyles[i];
            }
        }


    bool Coach::AddStyle(Style &style)
    {
        if (stylesCount >= constants::MAX_STYLES)
        {
            return false;
        }

        for (int i = 0; i < stylesCount; i++)
        {
            if (styles[i].GetId() == style.GetId())
            {
                return false;
            }
        }

        styles[stylesCount] = style;
        stylesCount++;

        return true;
    }

    bool Coach::RemoveStyle(int styleId)
    {
        int index = -1;

        for (int i = 0; i < stylesCount; i++)
        {
            if (styles[i].GetId() == styleId)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            return false;
        }

        for (int i = index; i < stylesCount - 1; i++)
        {
            styles[i] = styles[i + 1];
        }

        stylesCount--;

        return true;
    }
}