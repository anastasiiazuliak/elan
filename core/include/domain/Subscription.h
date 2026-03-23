#pragma once

namespace domain
{
    struct Subscription
    {
        int Id;
        char *Name;
        char *Category;
        int Duration;
        int ForOneWorkout;
        int ForEightWorkouts;
        int ForTwelweWorkouts;
    };
}