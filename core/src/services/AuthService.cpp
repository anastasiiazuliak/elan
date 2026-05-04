#include <cstring>

#include "elan/services/AuthService.h"
#include "elan/domain/Person.h"

namespace service
{
    AuthService::AuthService(storage::Storage<domain::Person> &persons) : persons(persons)
    {
    }

    domain::Person *AuthService::Login(const char *username, const char *password)
    {
        std::vector<domain::Person> allPersons = persons.GetAll();

        for (auto &p : allPersons)
        {
            if (strcmp(person.username, username) == 0 &&
                person.CheckPassword(password))
            {
                return &person;
            }
        }

        return nullptr;
    }
}