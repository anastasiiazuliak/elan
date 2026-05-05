#include "elan/domain/Coach.h"

namespace domain
{
    bool Coach::AddStyle(Style &style)
    {
        if (stylesCount >= constants::MAX_STYLES)
        {
            return false;
        }

        for (int i = 0; i < stylesCount; i++)
        {
            if (styles[i].GetId() == style.GetId())
            {
                return false;
            }
        }

        styles[stylesCount] = style;
        stylesCount++;

        return true;
    }

    bool Coach::RemoveStyle(int styleId)
    {
        int index = -1;

        for (int i = 0; i < stylesCount; i++)
        {
            if (styles[i].GetId() == styleId)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            return false;
        }

        for (int i = index; i < stylesCount - 1; i++)
        {
            styles[i] = styles[i + 1];
        }

        stylesCount--;

        return true;
    }
}