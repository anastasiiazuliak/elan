#pragma once

#include "Person.h"
#include "Style.h"

namespace domain
{
    class Coach : public Person
    {
        Style Styles[10];
        char Description[200];
    };
}
