#pragma once

#include "elan/domain/Person.h"
#include "elan/common/Category.h"

namespace domain
{
    class Client : public Person
    {
        Role role = Role::Client;
        common::Category category;

    public:
        Client();
        Client(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, const char *password, const char *username);

        common::Category GetCategory() const;

        // Удаліть
        void PrintClient();
    };
}
