#include "elan/domain/Subscription.h"

namespace domain
{
    void Subscription::SetId(int id)
    {
        this->id = id;
    }

    int Subscription::GetId() const
    {
        return id;
    }
}