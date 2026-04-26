#include "elan/domain/Style.h"

namespace domain
{
    void Style::SetId(int id)
    {
        this-> id= id;
    }

    int Style::GetId() const
    {
        return id;
    }
}