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
        int id;
        HallType type;
        int capacity;

        void SetTypeByCapacity(int capacity);

        Hall() = default;
        Hall(int capacity);


        //Удаліть
        void PrintHall();
    };
}
