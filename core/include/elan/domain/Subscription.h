#pragma once

#include "elan/domain/Client.h"

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    class Subscription
    {
        int Id;
        char Name[30];
        Categories Category;
        int Duration;
        int NumberOfWorkouts;

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        int GetId() const;
    };
}