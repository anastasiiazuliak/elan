#include "elan/dtos/HallDto.h"

#include <cstring>

namespace dtos
{
    HallDto ToDto(const domain::Hall &h)
    {
        return {
            h.id,
            h.name,
            h.capacity,
            static_cast<int>(h.type)
        };
    }

    domain::Hall FromDto(const HallDto &dto)
    {
        domain::Hall h;

        h.id = dto.id;
        h.capacity = dto.capacity;
        strcpy(h.name, dto.name.c_str());
        h.type = static_cast<domain::HallType>(dto.type);

        return h;
    }
}