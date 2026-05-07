#include "elan/domain/Person.h"
#include "elan/common/Utils.h"

#include <iostream>
#include <ctime>
#include <cstring>

namespace domain
{
    Person::Person()
    {
        id = 0;
        strcpy(firstName, "");
        strcpy(lastName, "");
        strcpy(patronymic, "");
        birthDate = common::Date(1, 1, 2000);
        strcpy(phone, "");
        strcpy(username, "");
    };

    Person::Person(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, const char *password, const char *username)
    {
        strcpy(this->firstName, firstName);
        strcpy(this->lastName, lastName);
        strcpy(this->patronymic, patronymic);
        this->birthDate = birthDate;
        strcpy(this->phone, phone);
        unsigned long p = utils::Hash(password);
        this->password = p;
        strcpy(this->username, username);
    };

    int Person::GetAge()
    {
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);

        int age = (now->tm_year + 1900) - birthDate.year;

        if ((birthDate.month > now->tm_mon + 1) ||
            (birthDate.month == now->tm_mon + 1 && birthDate.day > now->tm_mday))
        {
            age--;
        }

        return age;
    };

    void Person::SetId(int id)
    {
        this->id = id;
    }

    int Person::GetId() const
    {
        return id;
    }

    void Person::SetPassword(const char *password)
    {
        this->password = utils::Hash(password);
    }

    bool Person::CheckPassword(const char *password) const
    {
        return this->password == utils::Hash(password);
    }

}