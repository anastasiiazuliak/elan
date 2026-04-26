#pragma once

#include "elan/domain/Client.h"
#include "elan/common/Constants.h"

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
        Categories category;
        int duration;
        int numberOfWorkouts;

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        int GetId() const;
    };
}