#include "elan/domain/Subscription.h"
#include <cstring>

#include <iostream>

namespace domain
{

    Subscription::Subscription(const char *name, common::Category category, int duration, int numberOfWorkouts)
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

    const char *Subscription::GetName() const
    {
        return name;
    }

    const common::Category Subscription::GetCategory()
    {
        return category;
    }

    const int Subscription::GetDuration()
    {
        return duration;
    }

    const int Subscription::GetNumberOfWorkouts()
    {
        return numberOfWorkouts;
    }

    //Удаліть
    void Subscription::PrintSubscription()
    {
        std::cout << "========== SUBSCRIPTION ==========\n";

        std::cout << "ID: " << id << "\n";
        std::cout << "Name: " << name << "\n";

        std::cout << "Category: ";

        switch (category)
        {
        case common::Category::Age_3_5:
            std::cout << "3-5 years";
            break;
        case common::Category::Age_5_plus:
            std::cout << "5+ years";
            break;
        case common::Category::Age_6_plus:
            std::cout << "6+ years";
            break;
        case common::Category::Age_7_plus:
            std::cout << "7+ years";
            break;
        case common::Category::Age_10_12:
            std::cout << "10-12 years";
            break;
        case common::Category::Age_14_plus:
            std::cout << "14+ years";
            break;
        case common::Category::Age_16_plus:
            std::cout << "16+ years";
            break;
        }

        std::cout << "\nDuration: " << duration << " days\n";
        std::cout << "Workouts: " << numberOfWorkouts << "\n";

        std::cout << "\n";
    }
}