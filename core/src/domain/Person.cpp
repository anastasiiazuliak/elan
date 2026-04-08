#include <iostream>
#include <ctime>
#include <cstring>
#include "elan/domain/Person.h"

namespace domain
{
    Person::Person()
    {
        Id = 0;
        strcpy(FirstName, "");
        strcpy(LastName, "");
        strcpy(Patronymic, "");
        BirthDate = common::Date(1, 1, 2000);
        strcpy(Phone, "");
    };

    Person::Person(int Id, const char *FirstName, const char *LastName, const char *Patronymic, common::Date BirthDate, const char *Phone)
    {
        this->Id = Id;
        strcpy(this->FirstName, FirstName);
        strcpy(this->LastName, LastName);
        strcpy(this->Patronymic, Patronymic);
        this->BirthDate = BirthDate;
        strcpy(this->Phone, Phone);
    };
    
    int Person::getAge()
    {
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);

        int age = (now->tm_year + 1900) - BirthDate.Year;

        if ((BirthDate.Month > now->tm_mon + 1) ||
            (BirthDate.Month == now->tm_mon + 1 && BirthDate.Day > now->tm_mday))
        {
            age--;
        }

        return age;
    };
}