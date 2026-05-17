#pragma once

#include "elan/domain/Person.h"
#include "elan/common/Category.h"

namespace domain
{
    class Client : public Person
    {
        Role role = Role::Client;
        int subscriptionId;
        common::Category category;

    public:
        Client();
        Client(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, int subscriptionId, char* password, char *username);
        void ChangeSubscription(int subscriptionId);

        //Удаліть
        void PrintClient();
    };
}
