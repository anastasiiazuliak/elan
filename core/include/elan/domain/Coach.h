#pragma once

#include "elan/domain/Person.h"
#include "elan/domain/Style.h"

namespace domain
{
    class Coach : public Person
    {
        Style Styles[10];
        char Description[200];
    };
}
