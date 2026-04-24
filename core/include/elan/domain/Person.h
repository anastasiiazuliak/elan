#pragma once

#include "elan/common/Date.h"

namespace storage
{
    class ClientStorage
    {
    };
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

        
        friend class storage::ClientStorage;

    public:
        Person();
        Person(const char *FirstName, const char *LastName, const char *Patronymic, common::Date BirthDate, const char *Phone);
        int GetAge();

        int GetId() const;
    };

}