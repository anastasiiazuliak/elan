#include "elan/dtos/HallDto.h"

namespace dtos
{
    HallDto ToDto(const domain::Hall &h)
    {
        return {
            h.id,
            h.capacity,
            static_cast<int>(h.type)
        };
    }

    domain::Hall FromDto(const HallDto &dto)
    {
        domain::Hall h;

        h.id = dto.id;
        h.capacity = dto.capacity;
        h.type = static_cast<domain::HallType>(dto.type);

        return h;
    }
}