#pragma once

#include <optional>
#include <vector>

#include "elan/storage/Storages.h"
#include "elan/domain/Employee.h"
#include "elan/domain/Coach.h"
#include "elan/domain/Client.h"
#include "elan/domain/Admin.h"

#include "AuthResult.h"

namespace service
{
    class AuthService
    {
        template <typename T>
        static std::optional<AuthResult> TryAuth(const std::vector<T>& users, const char* username, const char* password, domain::Role role);

    public:
        static std::optional<AuthResult>
        Login(const char* username, const char* password);

        static void Logout(int userId);
    };
}