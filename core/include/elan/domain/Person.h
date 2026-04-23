#pragma once

#include "elan/common/Date.h"

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

    public:
        Person();
        Person(const char *FirstName, const char *LastName, const char *Patronymic, common::Date BirthDate, const char *Phone);
        int GetAge();

        void SetId(int id);
        int GetId() const;
    };

}