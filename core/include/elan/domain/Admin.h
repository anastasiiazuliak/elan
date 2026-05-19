#pragma once

#include "elan/domain/Person.h"

namespace domain
{
    class Admin : public Person
    {
        Role role = Role::Admin;

        public:
        Admin() = default;
        Admin(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, const char *password, const char *username);
    };
}