#pragma once

#include <string>

#include "elan/domain/Employee.h"

namespace dtos
{
    struct EmployeeRequestDto
    {
        std::string firstName;
        std::string lastName;
        std::string patronymic;
        std::string birthDate;
        std::string phone;
        int locationId;
        std::string password;
        std::string username;
    };

    struct EmployeeResponseDto
    {
        int id;
        std::string firstName;
        std::string lastName;
        std::string patronymic;
        std::string birthDate;
        std::string phone;
        int locationId;
        std::string username;
    };

    EmployeeResponseDto ToDto(const domain::Employee &e);
    domain::Employee FromDto(const EmployeeRequestDto &dto);
};