#include "elan/domain/Style.h"

#include <iostream>
#include <cstring>

namespace domain
{
    void Style::SetId(int id)
    {
        this->id = id;
    }

    int Style::GetId() const
    {
        return id;
    }

    Style::Style(const char *name, const char *description)
    {
        std::strncpy(this->name, name, constants::NAME_LENGTH);
        this->name[constants::NAME_LENGTH - 1] = '\0';

        std::strncpy(this->description, description, constants::DESCRIPTION_LENGTH);
        this->description[constants::DESCRIPTION_LENGTH - 1] = '\0';
    }

    const char* Style::GetName()
    {
        return name;
    }

    // Удаліть
    void Style::PrintStyle()
    {
        std::cout << "========== STYLE ==========\n";

        std::cout << "ID: " << id << "\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Description: " << description << "\n";

        std::cout << "\n";
    }
}