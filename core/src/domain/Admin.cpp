#include "elan/domain/Admin.h"

namespace domain
{
    Admin::Admin(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, const char *password, const char *username) : Person(firstName, lastName, patronymic, birthDate, phone, password, username)
    {
        role = Role::Admin;
    }
}