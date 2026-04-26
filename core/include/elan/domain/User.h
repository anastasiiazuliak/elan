#pragma once

namespace storage
{
    template <typename T>
    class Storage;
}

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

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        int GetId() const;
    };
}