#include "elan/dtos/StyleDto.h"

namespace dtos
{
    StyleDto ToDto(const domain::Style &s)
    {
        return {
            s.GetId(),
            s.GetName(),
            s.GetDescription()};
    }

    domain::Style FromDto(const dtos::StyleDto &dto)
    {
        return domain::Style(
            dto.name.c_str(),
            dto.description.c_str());
    }
}
