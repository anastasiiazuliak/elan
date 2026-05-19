#pragma once

#include "elan/common/Date.h"
#include "elan/common/Constants.h"

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    enum class Role
    {
        Admin,
        Client,
        Employee,
        Coach
    };

    class Person
    {
    protected:
        int id;
        char firstName[constants::NAME_LENGTH];
        char lastName[constants::NAME_LENGTH];
        char patronymic[constants::NAME_LENGTH];
        common::Date birthDate;
        char phone[constants::PHONE_LENGTH];
        Role role;
        unsigned long password;
        char username[constants::NAME_LENGTH];

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        Person();
        Person(const char *firstName, const char *lastName, const char *patronymic, common::Date birthDate, const char *phone, const char *password, const char *username);

        int GetAge();
        int GetId() const;
        Role GetRole();

        const char* GetUsername() const;

        void SetPassword(const char *password);
        bool CheckPassword(const char *password) const;
    };

}