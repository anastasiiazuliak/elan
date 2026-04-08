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
        SubscriptionId = 0;
        Category = Categories::Age_16_plus;
    };

    Client::Client(int Id, const char* FirstName, const char* LastName, const char* Patronymic, common::Date BirthDate, const char* Phone, int SubscriptionId) : Person(Id, FirstName, LastName, Patronymic, BirthDate, Phone)
    {
        this->SubscriptionId = SubscriptionId;
        int age = getAge();
        Category = determineCategory(age);
    }
}
