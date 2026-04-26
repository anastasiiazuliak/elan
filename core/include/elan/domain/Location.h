#pragma once

#include "elan/domain/Hall.h"

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    class Location
    {
        int Id;
        char Address[36];
        Hall Halls[5];

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        int GetId() const;
    };
}