#include "elan/domain/Schedule.h"

namespace domain 
{
    void Schedule::SetId(int id)
    {
        this->id = id;
    }

    int Schedule::GetId() const
    {
        return id;
    }
}