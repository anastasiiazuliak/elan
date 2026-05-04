#include "elan/domain/Group.h"

namespace domain
{
    void Group::SetId(int id)
    {
        this->id = id;
    }

    int Group::GetId() const
    {
        return id;
    }

    int Group::GetCoachId()
    {
        return coachId;
    }
}
