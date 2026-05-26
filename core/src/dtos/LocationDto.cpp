#include "elan/dtos/LocationDto.h"

namespace dtos
{
    LocationDto ToDto(const domain::Location &l)
    {
        return {
            l.GetId(),
            l.GetAddress(),
            l.GetHallCount()};
    }

    domain::Location FromDto(const LocationDto &dto)
    {
        return domain::Location(dto.address.c_str());
    }
}
