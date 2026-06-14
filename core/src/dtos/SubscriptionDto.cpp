#include "elan/dtos/SubscriptionDto.h"

namespace dtos
{
    SubscriptionDto ToDto(const domain::Subscription &s)
    {
        return {
            s.GetId(),
            s.GetName(),
            s.GetDuration(),
            s.GetNumberOfWorkouts(),
            s.GetPrice()
        };
    }

    domain::Subscription FromDto(const SubscriptionDto &dto)
    {
        return domain::Subscription(
            dto.name.c_str(),
            dto.duration,
            dto.numberOfWorkouts,
            dto.price
        );
    }
}
