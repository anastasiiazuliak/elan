#include "elan/domain/Subscription.h"
#include <cstring>

namespace domain
{
     Subscription::Subscription()
    {
        id = -1;
        name[0] = '\0';
        duration = 0;
        numberOfWorkouts = 0;
    }

    Subscription::Subscription(char *name, Category category, int duration, int numberOfWorkouts)
    {
        this->id = -1;

        std::strncpy(this->name, name, constants::NAME_LENGTH);
        this->name[constants::NAME_LENGTH - 1] = '\0';

        this->category = category;
        this->duration = duration;
        this->numberOfWorkouts = numberOfWorkouts;
    }

    void Subscription::SetId(int id)
    {
        this->id = id;
    }

    int Subscription::GetId() const
    {
        return id;
    }
}