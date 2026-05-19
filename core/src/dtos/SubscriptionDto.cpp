#include "elan/dtos/SubscriptionDto.h"

namespace dtos
{
    SubscriptionDto ToDto(const domain::Subscription &s)
    {
        return {
            s.GetId(),
            s.GetName(),
            s.GetCategory(),
            s.GetDuration(),
            s.GetNumberOfWorkouts()
        };
    }

    domain::Subscription FromDto(const SubscriptionDto &dto)
    {
        return domain::Subscription (
            dto.name.c_str(),
            dto.category,
            dto.duration,
            dto.numberOfWorkouts
        );
    }
}