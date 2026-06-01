#include "elan/services/AuthService.h"

#include <cstring>

namespace service
{
    storage::Storage<domain::Employee> AuthService::employees(
        constants::EMPLOYEES_FILE,
        constants::EMPLOYEES_ID_FILE);

    storage::Storage<domain::Coach> AuthService::coaches(
        constants::COACHES_FILE,
        constants::COACHES_ID_FILE);

    storage::Storage<domain::Client> AuthService::clients(
        constants::CLIENTS_FILE,
        constants::CLIENTS_ID_FILE);

    storage::Storage<domain::Admin> AuthService::admin(
        constants::ADMIN_FILE,
        constants::ADMIN_ID_FILE);

    template <typename T>
    std::optional<AuthResult> AuthService::TryAuth(const std::vector<T>& users, const char* username, const char* password, domain::Role role)
    {
        for (const auto& u : users)
        {
            if (strcmp(u.GetUsername(), username) == 0 &&
                u.CheckPassword(password))
            {
                return AuthResult{
                    u.GetId(),
                    u.GetUsername(),
                    role
                };
            }
        }

        return std::nullopt;
    }

    std::optional<AuthResult>
    AuthService::Login(const char* username, const char* password)
    {
        if (auto r = TryAuth(clients.GetAll(), username, password, domain::Role::Client))
            return r;

        if (auto r = TryAuth(employees.GetAll(), username, password, domain::Role::Employee))
            return r;

        if (auto r = TryAuth(coaches.GetAll(), username, password, domain::Role::Coach))
            return r;

        if (auto r = TryAuth(admin.GetAll(), username, password, domain::Role::Admin))
            return r;

        return std::nullopt;
    }

    void AuthService::Logout(int userId)
    {
        // stateless auth → поки заглушка
        // майбутнє: JWT blacklist або sessions
    }
}