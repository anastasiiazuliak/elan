#pragma once

#include "elan/domain/Hall.h"

namespace domain
{
    class Location
    {
        int Id;
        char Address[36];
        Hall Halls[5];
    };
}