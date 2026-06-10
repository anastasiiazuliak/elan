#pragma once

#include "elan/common/constants.h"

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
        char name[constants::NAME_LENGTH];
        HallType type;
        int capacity;

        void SetTypeByCapacity(int capacity);

        Hall() = default;
        Hall(const char *name, int capacity);


        //Удаліть
        void PrintHall();
    };
}
