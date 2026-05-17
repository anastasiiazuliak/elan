#pragma once

#include "elan/domain/Person.h"
#include "elan/common/Constants.h"

namespace domain
{
    class Employee : public Person
    {
        int locationId;
        char email[constants::EMAIL_LENGTH];

    public:
        Employee() = default;
        Employee(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, int locationId, const char *email, const char *password, const char *username);

        // Удаліть
        void PrintEmployee();
    };
}
