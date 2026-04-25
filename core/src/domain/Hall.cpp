#include "elan/domain/Hall.h"

namespace domain
{
    void Hall::SetId(int id)
    {
        Id = id;
    }

    int Hall::GetId() const
    {
        return Id;
    }
}