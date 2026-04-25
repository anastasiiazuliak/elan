#pragma once

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    struct Style
    {
        int Id;
        char Name[30];
        char Description[200];

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        int GetId() const;
    };
}
