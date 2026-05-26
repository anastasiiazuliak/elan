#include "elan/domain/Client.h"

#include <iostream>

namespace domain
{
    Client::Client() : Person()
    {
        subscriptionId = 0;
        category = common::Category::Age_16_plus;
    };

    Client::Client(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, int subscriptionId, const char *password, const char *username) : Person(firstName, lastName, patronymic, birthDate, phone, password, username)
    {
        this->subscriptionId = subscriptionId;
        int age = GetAge();
        category = common::determineCategory(age);
    }

    int Client::GetSubscriptionId() const
    {
        return subscriptionId;
    }

    void Client::ChangeSubscription(int subscriptionId)
    {
        this->subscriptionId = subscriptionId;
    }

    // Удаліть
    void Client::PrintClient()
    {
        std::cout << "========== CLIENT ==========\n";

        std::cout << "ID: " << id << "\n";

        std::cout << "Name: "
                  << firstName << " "
                  << lastName << " "
                  << patronymic << "\n";

        std::cout << "Phone: "
                  << phone << "\n";

        std::cout << "Subscription: "
                  << subscriptionId << " ";

        std::cout << "\n";

        std::cout << "Category: ";
        switch (category)
        {
        case common::Category::Age_3_5:
            std::cout << "3-5 years";
            break;

        case common::Category::Age_5_plus:
            std::cout << "5+";
            break;

        case common::Category::Age_6_plus:
            std::cout << "6+";
            break;

        case common::Category::Age_7_plus:
            std::cout << "7+";
            break;

        case common::Category::Age_10_12:
            std::cout << "10-12";
            break;

        case common::Category::Age_14_plus:
            std::cout << "14+";
            break;

        case common::Category::Age_16_plus:
            std::cout << "16+";
            break;
        }

        std::cout << "\n";
        std::cout << "\n";
    }
}
