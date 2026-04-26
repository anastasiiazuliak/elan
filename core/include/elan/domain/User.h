#pragma once

#include "elan/common/Constants.h"

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    enum class Role
    {
        Admin,
        Client,
        Employee,
        Coach
    };

    class User
    {
        int id;
        int personId;
        Role role;
        char username[constants::NAME_LENGTH];

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        int GetId() const;
    };
}