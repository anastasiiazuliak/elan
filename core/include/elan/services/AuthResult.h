#pragma once

#include "elan/domain/Person.h"

#include <string>

namespace service
{
    struct AuthResult
    {
        int id;
        std::string username;
        domain::Role role;
    };
}