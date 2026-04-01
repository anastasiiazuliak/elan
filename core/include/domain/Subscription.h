#pragma once

#include "Client.h"

namespace domain
{
    class Subscription
    {
        int Id;
        char Name[30];
        Categories Category;
        int Duration;
        int NumberOfWorkouts;
    };
}