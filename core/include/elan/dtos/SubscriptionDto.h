#pragma once 

#include "elan/domain/Subscription.h"

#include <cstring>
#include <iostream>

namespace dtos
{
    struct SubscriptionDto
    {
        int id;
        std::string name;
        int duration;
        int numberOfWorkouts;
        int price;
    };

    SubscriptionDto ToDto(const domain::Subscription &s);
    domain::Subscription FromDto(const SubscriptionDto &dto);
}
