#pragma once

namespace domain
{
    enum class Role
    {
        Client,
        Employee,
        Coach
    };

    class User
    {
        int Id;
        int PersonId;
        Role Role;
        char Username[20];
    };
}