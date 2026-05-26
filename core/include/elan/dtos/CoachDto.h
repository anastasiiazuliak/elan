#pragma once

#include <string>
#include <vector>

#include "elan/domain/Coach.h"

namespace dtos
{
    struct CoachRequestDto
    {
        std::string firstName;
        std::string lastName;
        std::string patronymic;
        std::string birthDate;
        std::string phone;
        std::string description;
        std::string password;
        std::string username;

        std::vector<int> styleIds;
    };

    struct CoachResponseDto
    {
        int id;
        std::string firstName;
        std::string lastName;
        std::string patronymic;
        std::string birthDate;
        std::string phone;
        std::string description;
        std::string username;

        std::vector<int> styleIds;
    };

    CoachResponseDto ToDto(const domain::Coach &c);
    domain::Coach FromDto(const CoachRequestDto &dto);
}
