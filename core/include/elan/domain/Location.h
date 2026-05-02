#pragma once

#include "elan/domain/Hall.h"
#include "elan/common/Constants.h"
#include "elan/domain/Schedule.h"

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    class Location
    {
        int id;
        char address[constants::ADDRES_LENGTH];
        Hall halls[constants::MAX_HALLS];
        Schedule schedule[constants::WORKING_DAYS][constants::WORKING_HOURS][constants::MAX_HALLS];

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        int GetId() const;
    };
}