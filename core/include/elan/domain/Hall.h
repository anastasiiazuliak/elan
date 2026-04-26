#pragma once

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    enum class HallType
    {
        Large,
        Medium,
        Individual
    };

    class Hall
    {
        int id;
        HallType type;
        int capacity;

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        int GetId() const;
    };
}
