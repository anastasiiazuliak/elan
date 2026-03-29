#pragma once 

#include "Person.h"

namespace domain
{
    class Employee : public Person
    {
        int LocationId;
        char Email[40];
    };
}
