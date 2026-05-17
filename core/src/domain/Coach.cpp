#include "elan/domain/Coach.h"

#include <cstring>
#include <iostream>

namespace domain
{
    Coach::Coach(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, const char *description, const char *password, const char *username) : Person(firstName, lastName, patronymic, birthDate, phone, password, username)
    {
        strcpy(this->description, description);
    }

    bool Coach::AddStyle(const Style &style)
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

    // Удаліть
    void Coach::PrintCoach()
    {
        std::cout << "========== COACH ==========\n";

        std::cout << "ID: " << id << "\n";

        std::cout << "Name: "
                  << firstName << " "
                  << lastName << " "
                  << patronymic << "\n";

        std::cout << "Phone: "
                  << phone << "\n";

        std::cout << "Description: "
                  << description << "\n";

        std::cout << "Styles:\n";

        for (int i = 0; i < stylesCount; i++)
        {
            std::cout << "- "
                      << styles[i].GetName()
                      << "\n";
        }

        std::cout << "\n";
    }
}