#include "elan/domain/Location.h"

namespace domain
{
    void Location::SetId(int id)
    {
        this->id = id;
    }

    int Location::GetId() const
    {
        return id;
    }
}