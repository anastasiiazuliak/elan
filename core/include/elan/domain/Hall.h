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

    struct Hall
    {
        int id;
        HallType type;
        int capacity;

        void SetId(int id);
        void SetTypeByCapacity(int capacity);

        template <typename T>
        friend class storage::Storage;

    public:
        Hall();
        Hall(int capacity);

        int GetId() const;
    };
}
