#pragma once

#include "elan/domain/Person.h"
#include "elan/common/Constants.h"

namespace domain
{
    class Employee : public Person
    {
        int locationId;

    public:
        Employee() = default;
        Employee(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, int locationId, const char *password, const char *username);

        int GetLocationId() const;

        // Удаліть
        void PrintEmployee();
    };
}
