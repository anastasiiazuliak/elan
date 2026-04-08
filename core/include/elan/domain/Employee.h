#pragma once

#include "elan/domain/Person.h"

namespace domain
{
    class Employee : public Person
    {
        int LocationId;
        char Email[40];
    };
}
