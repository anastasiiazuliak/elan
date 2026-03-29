#pragma once
 
#include "Person.h"

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

    class Client : public Person
    {
        int SubscriptionId;
        Categories Category;
    };
}
