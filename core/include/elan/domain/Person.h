#pragma once

#include "elan/common/Date.h"

namespace storage
{
    template <typename T>
    class Storage;
}

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

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        Person();
        Person(const char *FirstName, const char *LastName, const char *Patronymic, common::Date BirthDate, const char *Phone);
        int GetAge();

        int GetId() const;
    };

}