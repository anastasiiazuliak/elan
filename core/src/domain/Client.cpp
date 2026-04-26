#include "elan/domain/Client.h"

namespace domain
{
    Categories determineCategory(int age)
    {
        if (age >= 3 && age <= 5)
            return Categories::Age_3_5;
        if (age > 5 && age <= 6)
            return Categories::Age_5_plus;
        if (age > 6 && age <= 7)
            return Categories::Age_6_plus;
        if (age > 7 && age <= 10)
            return Categories::Age_7_plus;
        if (age > 10 && age <= 12)
            return Categories::Age_10_12;
        if (age > 12 && age <= 14)
            return Categories::Age_14_plus;
        return Categories::Age_16_plus;
    };

    Client::Client() : Person()
    {
        subscriptionId = 0;
        category = Categories::Age_16_plus;
    };

    Client::Client(const char* firstName, const char* lastName, const char* patronymic, common::Date birthDate, const char* phone, int subscriptionId) : Person(firstName, lastName, patronymic, birthDate, phone)
    {
        this->subscriptionId = subscriptionId;
        int age = GetAge();
        category = determineCategory(age);
    }
}
