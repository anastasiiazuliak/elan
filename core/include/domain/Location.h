#pragma once

#include "Hall.h"

namespace domain
{
    struct Location
    {
        int Id;
        char Address;
        Hall *Halls[];
    };
}