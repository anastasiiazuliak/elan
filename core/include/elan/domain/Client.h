#pragma once
#include "elan/domain/Person.h"

namespace domain
{
    enum class Categories
    {
        Age_3_5,
        Age_5_plus,
        Age_6_plus,
        Age_7_plus,
        Age_10_12,
        Age_14_plus,
        Age_16_plus
    };
    Categories determineCategory(int age);

    class Client : public Person
    {
        int SubscriptionId;
        Categories Category;

    public:
        Client();
        Client(int Id, const char *FirstName, const char *LastName, const char *Patronymic, common::Date BirthDate, const char *Phone, int SubscriptionId);
    };
}
