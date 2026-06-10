#include "elan/domain/Coach.h"

#include <cstring>
#include <iostream>

namespace domain
{
    Coach::Coach(
        const char *firstName,
        const char *lastName,
        const char *patronymic,
        common::Date birthDate,
        const char *phone,
        const char *description,
        const char *password,
        const char *username)
        : Person(firstName, lastName, patronymic, birthDate, phone, password, username)
    {
        stylesCount = 0;
        memset(styles, 0, sizeof(styles));
        memset(this->description, 0, sizeof(this->description));

        strcpy(this->description, description);
    }

    const int *Coach::GetStyleIds() const
    {
        return styles;
    }

    int Coach::GetStylesCount() const
    {
        return stylesCount;
    }

    const char *Coach::GetDescription() const
    {
        return description;
    }

    bool Coach::AddStyle(int styleId)
    {
        if (styleId <= 0)
            return false;

        if (stylesCount >= constants::MAX_STYLES)
            return false;

        for (int i = 0; i < stylesCount; i++)
        {
            if (styles[i] == styleId)
                return false;
        }

        styles[stylesCount++] = styleId;
        return true;
    }

    bool Coach::RemoveStyle(int styleId)
    {
        int index = -1;

        for (int i = 0; i < stylesCount; i++)
        {
            if (styles[i] == styleId)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            return false;

        for (int i = index; i < stylesCount - 1; i++)
        {
            styles[i] = styles[i + 1];
        }

        styles[--stylesCount] = 0;

        return true;
    }

    void Coach::PrintCoach()
    {
        std::cout << "========== COACH ==========\n";

        std::cout << "ID: " << id << "\n";

        std::cout << "Name: "
                  << firstName << " "
                  << lastName << " "
                  << patronymic << "\n";

        std::cout << "Phone: " << phone << "\n";

        std::cout << "Description: " << description << "\n";

        std::cout << "Styles:\n";

        for (int i = 0; i < stylesCount; i++)
        {
            std::cout << "- " << styles[i] << "\n";
        }

        std::cout << "\n";
    }
}