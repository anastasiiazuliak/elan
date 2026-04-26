#pragma once

#include "elan/domain/Person.h"
#include "elan/common/Constants.h"

namespace domain
{
    class Employee : public Person
    {
        int locationId;
        char email[constants::EMAIL_LENGTH];
    };
}
