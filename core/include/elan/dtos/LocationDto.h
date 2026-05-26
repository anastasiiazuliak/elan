#pragma once

#include <string>

#include "elan/domain/Location.h"

namespace dtos
{
    struct LocationDto
    {
        int id;
        std::string address;
        int hallCount;
    };

    LocationDto ToDto(const domain::Location &l);
    domain::Location FromDto(const LocationDto &dto);
}