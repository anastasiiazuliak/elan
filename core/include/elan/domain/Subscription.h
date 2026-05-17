#pragma once

#include "elan/common/Constants.h"
#include "elan/common/Category.h"

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
        Subscription(char *name, common::Category category, int duration, int numberOfWorkouts);
        int GetId() const;
        const char* GetName() const;

        //Удаліть
        void PrintSubscription();
    };
}