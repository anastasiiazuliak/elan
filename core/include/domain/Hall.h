#pragma once

namespace domain
{
    enum class HallType
    {
        Large, 
        Medium, 
        Individual
    };

    struct Hall
    {
        int Id;
        HallType Type;
        int Capacity;
    };
}
