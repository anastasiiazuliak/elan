#include "elan/domain/Employee.h"
#include <cstring>

#include <iostream>

namespace domain
{
    Employee::Employee(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, int locationId, const char *email, const char *password, const char *username) : Person(firstName, lastName, patronymic, birthDate, phone, password, username)
    {
        this->locationId = locationId;
        strncpy(this->email, email, constants::EMAIL_LENGTH - 1);
        this->email[constants::EMAIL_LENGTH - 1] = '\0';
    }

    int Employee::GetLocationId() const
    {
        return locationId;
    }

    const char *Employee::GetEmail() const
    {
        return email;
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

        std::cout << "Email: "
                  << email << "\n";

        std::cout << "Location ID: "
                  << locationId << "\n";

        std::cout << "\n";
    }
}