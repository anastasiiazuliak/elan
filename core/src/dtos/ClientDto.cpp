#include "elan/dtos/ClientDto.h"

namespace dtos
{
    ClientResponseDto ToDto(const domain::Client &c)
    {
        return {
            c.GetId(),
            c.GetFirstName(),
            c.GetLastName(),
            c.GetPatronymic(),
            common::FormatDate(c.GetBirthDate()),
            c.GetPhone(),
            c.GetUsername(),
            c.GetSubscriptionId()};
    }

    domain::Client FromDto(const ClientRequestDto &dto)
    {
        return domain::Client(
            dto.firstName.c_str(),
            dto.lastName.c_str(),
            dto.patronymic.c_str(),
            common::ParseDate(dto.birthDate),
            dto.phone.c_str(),
            dto.subscriptionId,
            dto.password.c_str(),
            dto.username.c_str());
    }
}
