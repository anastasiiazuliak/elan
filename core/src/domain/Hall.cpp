#include "elan/domain/Hall.h"

namespace domain
{
    void Hall::SetId(int id)
    {
        this->id = id;
    }

    int Hall::GetId() const
    {
        return id;
    }
}