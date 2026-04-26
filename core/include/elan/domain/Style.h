#pragma once

#include "elan/common/Constants.h"

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    struct Style
    {
        int id;
        char name[constants::NAME_LENGTH];
        char description[constants::DESCRIPTION_LENGTH];

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        int GetId() const;
    };
}
