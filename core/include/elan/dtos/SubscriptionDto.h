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
        common::Category category;
        int duration;
        int numberOfWorkouts;
    };

    SubscriptionDto ToDto(const domain::Subscription &s);
    domain::Subscription FromDto(const SubscriptionDto &dto);
}