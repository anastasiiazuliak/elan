#include "elan/domain/Style.h"

namespace domain
{
    void Style::SetId(int id)
    {
        Id = id;
    }

    int Style::GetId() const
    {
        return Id;
    }
}