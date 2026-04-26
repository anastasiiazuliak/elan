#include "elan/domain/Subscription.h"

namespace domain
{
    void Subscription::SetId(int id)
    {
        Id = id;
    }

    int Subscription::GetId() const
    {
        return Id;
    }
}