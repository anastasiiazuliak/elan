#include <iostream>
#include <ctime>
#include <cstring>
#include "elan/domain/Person.h"

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
    };

    Person::Person(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone)
    {
        strcpy(this->firstName, firstName);
        strcpy(this->lastName, lastName);
        strcpy(this->patronymic, patronymic);
        this->birthDate = birthDate;
        strcpy(this->phone, phone);
    };
    
    int Person::GetAge()
    {
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);

        int age = (now->tm_year + 1900) - birthDate.Year;

        if ((birthDate.Month > now->tm_mon + 1) ||
            (birthDate.Month == now->tm_mon + 1 && birthDate.Day > now->tm_mday))
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
}