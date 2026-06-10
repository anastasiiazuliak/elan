#pragma once

#include "elan/domain/Hall.h"
#include <string>

namespace dtos
{
    struct HallDto
    {
        int id;
        std::string name;
        int capacity;
        int type;
    };

    HallDto ToDto(const domain::Hall &h);
    domain::Hall FromDto(const HallDto &dto);
}