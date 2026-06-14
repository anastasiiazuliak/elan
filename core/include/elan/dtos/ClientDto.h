#pragma once

#include <string>

#include "elan/domain/Client.h"

namespace dtos
{
    struct ClientRequestDto
    {
        std::string firstName;
        std::string lastName;
        std::string patronymic;
        std::string birthDate;
        std::string phone;
        std::string password;
        std::string username;
    };

    struct ClientResponseDto
    {
        int id;
        std::string firstName;
        std::string lastName;
        std::string patronymic;
        std::string birthDate;
        std::string phone;
        std::string username;
        common::Category category;
    };

    ClientResponseDto ToDto(const domain::Client &c);
    domain::Client FromDto(const ClientRequestDto &dto);
}
