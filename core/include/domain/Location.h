#pragma once

#include "Hall.h"

namespace domain
{
    class Location
    {
        int Id;
        char Address;
        Hall Halls[5];
    };
}