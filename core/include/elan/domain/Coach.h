#pragma once

#include "elan/domain/Person.h"
#include "elan/domain/Style.h"
#include "elan/common/Constants.h"

namespace domain
{
    class Coach : public Person
    {
        Style styles[constants::MAX_STYLES];
        int stylesCount = 0;
        char description[constants::DESCRIPTION_LENGTH];

    public:
        Coach() = default;
        Coach(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone,  const char *description, const char* password, const char *username);
        bool AddStyle(const Style &style);
        bool RemoveStyle(int styleId);

        //Удаліть
        void PrintCoach();
    };
}
