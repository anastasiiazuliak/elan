#pragma once

#include "../common/Date.h"

namespace domain
{
    class Person
    {
        int Id;
        char FirstName[20];
        char LastName[20];
        char Patronymic[20];
        common::Date BirthDate;
        char Phone[13];
    };
}