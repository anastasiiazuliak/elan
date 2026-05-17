#include "elan/common/Utils.h"

namespace utils
{
    unsigned long Hash(const std::string &password)
    {
        unsigned long hash = 5381;

        for (char c : password)
        {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }

        return hash;
    }
}