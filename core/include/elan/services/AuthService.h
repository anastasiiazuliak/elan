#pragma once

#include <optional>
#include <vector>

#include "elan/storage/Storage.h"
#include "elan/domain/Employee.h"
#include "elan/domain/Coach.h"
#include "elan/domain/Client.h"
#include "elan/domain/Admin.h"

#include "AuthResult.h"

namespace service
{
    class AuthService
    {
        static storage::Storage<domain::Employee> employees;
        static storage::Storage<domain::Coach> coaches;
        static storage::Storage<domain::Client> clients;
        static storage::Storage<domain::Admin> admin;

        template <typename T>
        static std::optional<AuthResult> TryAuth(const std::vector<T>& users, const char* username, const char* password, domain::Role role);

    public:
        static std::optional<AuthResult>
        Login(const char* username, const char* password);

        static void Logout(int userId);
    };
}