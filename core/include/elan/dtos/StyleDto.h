#pragma once

#include "elan/domain/Style.h"

#include <cstring>
#include <iostream>

namespace dtos
{
    struct StyleDto
    {
        int id;
        std::string name;
        std::string description;
    };

    StyleDto ToDto(const domain::Style &s);
    domain::Style FromDto(const StyleDto &dto);
}