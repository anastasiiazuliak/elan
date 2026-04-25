#include "elan/domain/Location.h"

namespace domain
{
    void Location::SetId(int id)
    {
        Id = id;
    }

    int Location::GetId() const
    {
        return Id;
    }
}