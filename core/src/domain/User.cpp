#include "elan/domain/User.h"

namespace domain
{
    void User::SetId(int id)
    {
        Id = id;
    }

    int User::GetId() const
    {
        return Id;
    }
}