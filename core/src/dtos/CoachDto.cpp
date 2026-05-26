#include "elan/dtos/CoachDto.h"

namespace dtos
{
    CoachResponseDto ToDto(const domain::Coach &c)
    {
        CoachResponseDto dto{
            c.GetId(),
            c.GetFirstName(),
            c.GetLastName(),
            c.GetPatronymic(),
            common::FormatDate(c.GetBirthDate()),
            c.GetPhone(),
            c.GetDescription(),
            c.GetUsername()};

        for (int i = 0; i < c.GetStylesCount(); i++)
        {
            dto.styleIds.push_back(
                c.GetStyleIds()[i]);
        }

        return dto;
    }

    domain::Coach FromDto(const CoachRequestDto &dto)
    {
        domain::Coach coach(
            dto.firstName.c_str(),
            dto.lastName.c_str(),
            dto.patronymic.c_str(),
            common::ParseDate(dto.birthDate),
            dto.phone.c_str(),
            dto.description.c_str(),
            dto.password.c_str(),
            dto.username.c_str());

        for (int styleId : dto.styleIds)
        {
            coach.AddStyle(styleId);
        }

        return coach;
    }
}