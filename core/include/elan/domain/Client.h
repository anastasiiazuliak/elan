#pragma once
#include "elan/domain/Person.h"

namespace domain
{
    enum class Category
    {
        Age_3_5,
        Age_5_plus,
        Age_6_plus,
        Age_7_plus,
        Age_10_12,
        Age_14_plus,
        Age_16_plus
    };

    Category determineCategory(int age);

    class Client : public Person
    {
        Role role = Role::Client;
        int subscriptionId;
        Category category;

    public:
        Client();
        Client(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, int subscriptionId, char* password, char *username);
        void ChangeSubscription(int subscriptionId);
    };
}
