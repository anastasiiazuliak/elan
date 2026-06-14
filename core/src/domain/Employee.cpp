#include "elan/domain/Employee.h"
#include <cstring>

#include <iostream>

namespace domain
{
    Employee::Employee(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, int locationId, const char *password, const char *username) : Person(firstName, lastName, patronymic, birthDate, phone, password, username)
    {
        this->locationId = locationId;
    }

    int Employee::GetLocationId() const
    {
        return locationId;
    }

    // Удаліть
    void Employee::PrintEmployee()
    {
        std::cout << "========== EMPLOYEE ==========\n";

        std::cout << "ID: " << id << "\n";

        std::cout << "Name: "
                  << firstName << " "
                  << lastName << " "
                  << patronymic << "\n";

        std::cout << "Phone: "
                  << phone << "\n";

        std::cout << "Location ID: "
                  << locationId << "\n";

        std::cout << "\n";
    }
}