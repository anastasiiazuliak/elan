#include "elan/services/AuthService.h"

#include <cstring>

namespace service
{
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
        if (auto r = TryAuth(storages::Clients().GetAll(), username, password, domain::Role::Client))
            return r;

        if (auto r = TryAuth(storages::Employees().GetAll(), username, password, domain::Role::Employee))
            return r;

        if (auto r = TryAuth(storages::Coaches().GetAll(), username, password, domain::Role::Coach))
            return r;

        if (auto r = TryAuth(storages::Admins().GetAll(), username, password, domain::Role::Admin))
            return r;

        return std::nullopt;
    }

    void AuthService::Logout(int userId)
    {
        // stateless auth → поки заглушка
        // майбутнє: JWT blacklist або sessions
    }
}