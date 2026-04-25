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
        int Id;
        HallType Type;
        int Capacity;

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        int GetId() const;
    };
}
