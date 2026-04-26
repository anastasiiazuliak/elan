#include "elan/domain/Group.h"

namespace domain
{
    void Group::SetId(int id)
    {
        Id = id;
    }

    int Group::GetId() const
    {
        return Id;
    }
}
