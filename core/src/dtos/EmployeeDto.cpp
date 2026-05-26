#include "elan/dtos/EmployeeDto.h"

namespace dtos
{
    EmployeeResponseDto ToDto(const domain::Employee &e)
    {
        return {
            e.GetId(),
            e.GetFirstName(),
            e.GetLastName(),
            e.GetPatronymic(),
            common::FormatDate(e.GetBirthDate()),
            e.GetPhone(),
            e.GetLocationId(),
            e.GetEmail(),
            e.GetUsername()};
    }

    domain::Employee FromDto(const EmployeeRequestDto &dto)
    {
        return domain::Employee(
            dto.firstName.c_str(),
            dto.lastName.c_str(),
            dto.patronymic.c_str(),
            common::ParseDate(dto.birthDate),
            dto.phone.c_str(),
            dto.locationId,
            dto.email.c_str(),
            dto.password.c_str(),
            dto.username.c_str());
    }
}
