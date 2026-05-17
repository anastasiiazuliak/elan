#include "elan/domain/Hall.h"
#include <stdexcept>

#include <iostream>

namespace domain
{
    void Hall::SetTypeByCapacity(int capacity)
    {
        if (capacity <= 8)
        {
            type = HallType::Individual;
        }
        else if (capacity <= 15)
        {
            type = HallType::Medium;
        }
        else // 16–25
        {
            type = HallType::Large;
        }
    }

    Hall::Hall(int capacity)
    {
        if (capacity <= 0 || capacity > 25)
        {
            throw std::invalid_argument("Invalid hall capacity");
        }

        this->capacity = capacity;
        SetTypeByCapacity(capacity);
    }

    //Удаліть
    void Hall::PrintHall()
    {
        std::cout << "========== HALL ==========\n";

        std::cout << "ID: " << id << "\n";

        std::cout << "Type: ";

        switch (type)
        {
        case HallType::Individual:
            std::cout << "Individual";
            break;

        case HallType::Medium:
            std::cout << "Medium";
            break;

        case HallType::Large:
            std::cout << "Large";
            break;
        }

        std::cout << "\nCapacity: " << capacity << "\n";

        std::cout << "\n";
    }
}