#pragma once

#include "elan/common/Constants.h"
#include "elan/common/Category.h"

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
        common::Category category;
        int duration;
        int numberOfWorkouts;

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        Subscription() = default;
        Subscription(const char* name, common::Category category, int duration, int numberOfWorkouts);
        int GetId() const;
        const char* GetName() const;
        const common::Category GetCategory() const;
        const int GetDuration() const;
        const int GetNumberOfWorkouts() const;

        //Удаліть
        void PrintSubscription();
    };
}