#include "elan/domain/User.h"

namespace domain
{
    void User::SetId(int id)
    {
        this->id = id;
    }

    int User::GetId() const
    {
        return id;
    }
}