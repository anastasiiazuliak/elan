#pragma once

#include "elan/domain/Person.h"
#include "elan/domain/Style.h"
#include "elan/common/Constants.h"

namespace domain
{
    class Coach : public Person
    {
        Style styles[constants::MAX_STYLES];
        int stylesCount = 0;
        char description[constants::DESCRIPTION_LENGTH];

    public:
        bool AddStyle(Style &style);
        bool RemoveStyle(int styleId);
    };
}
