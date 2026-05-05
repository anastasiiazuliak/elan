#include "elan/domain/Hall.h"
#include <stdexcept>

namespace domain
{
    Hall::Hall()
    {
        id = -1;
        type = HallType::Medium;
        capacity = 10;
    }

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

    void Hall::SetId(int id)
    {
        this->id = id;
    }

    int Hall::GetId() const
    {
        return id;
    }
}