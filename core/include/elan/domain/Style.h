#pragma once

#include "elan/common/Constants.h"

namespace storage
{
    template <typename T>
    class Storage;
}

namespace domain
{
    class Style
    {
        int id;
        char name[constants::NAME_LENGTH];
        char description[constants::DESCRIPTION_LENGTH];

        void SetId(int id);

        template <typename T>
        friend class storage::Storage;

    public:
        Style() = default;
        Style(const char *name, const char *description);
        int GetId() const;

        // Удаліть
        void PrintStyle();
        const char* GetName();
    };
}
