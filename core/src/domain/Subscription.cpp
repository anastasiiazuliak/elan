#include "elan/domain/Subscription.h"
#include <cstring>

#include <iostream>

namespace domain
{

    Subscription::Subscription(const char *name, int duration, int numberOfWorkouts, int price)
    {
        this->id = -1;

        std::strncpy(this->name, name, constants::NAME_LENGTH);
        this->name[constants::NAME_LENGTH - 1] = '\0';

        this->duration = duration;
        this->numberOfWorkouts = numberOfWorkouts;
        this->price = price;
    }

    void Subscription::SetId(int id)
    {
        this->id = id;
    }

    int Subscription::GetId() const
    {
        return id;
    }

    const char *Subscription::GetName() const
    {
        return name;
    }

    const int Subscription::GetDuration() const
    {
        return duration;
    }

    const int Subscription::GetNumberOfWorkouts() const
    {
        return numberOfWorkouts;
    }

    const int Subscription::GetPrice() const
    {
        return price;
    }

    //Удаліть
    void Subscription::PrintSubscription()
    {
        std::cout << "========== SUBSCRIPTION ==========\n";

        std::cout << "ID: " << id << "\n";
        std::cout << "Name: " << name << "\n";

        std::cout << "Category: ";

        std::cout << "\nDuration: " << duration << " days\n";
        std::cout << "Workouts: " << numberOfWorkouts << "\n";

        std::cout << "\n";
    }
}
