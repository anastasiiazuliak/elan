#pragma once

#include "elan/common/Constants.h"

#include <cstring>
#include <iostream>

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    class Subscription
    {
        int id;
        char name[constants::NAME_LENGTH];
        int duration;
        int numberOfWorkouts;
        int price;

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        Subscription() = default;
        Subscription(const char* name, int duration, int numberOfWorkouts, int price);
        int GetId() const;
        const char* GetName() const;
        const int GetDuration() const;
        const int GetNumberOfWorkouts() const;
        const int GetPrice() const;

        //Удаліть
        void PrintSubscription();
    };
}
