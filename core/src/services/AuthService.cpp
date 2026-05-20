#include <cstring>

#include "elan/services/AuthService.h"

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

    std::unique_ptr<domain::Person>
    AuthService::Login(const char *username, const char *password)
    {
        auto cl = clients.GetAll();

        for (auto &c : cl)
        {
            if (strcmp(c.GetUsername(), username) == 0 &&
                c.CheckPassword(password))
            {
                return std::make_unique<domain::Client>(c);
            }
        }

        auto em = employees.GetAll();

        for (auto &e : em)
        {
            if (strcmp(e.GetUsername(), username) == 0 &&
                e.CheckPassword(password))
            {
                return std::make_unique<domain::Employee>(e);
            }
        }

        auto coa = coaches.GetAll();

        for (auto &co : coa)
        {
            if (strcmp(co.GetUsername(), username) == 0 && co.CheckPassword(password))
            {
                return std::make_unique<domain::Coach>(co);
            }
        }

        auto ad = admin.GetAll();

        for (auto &a : ad)
        {
            if (strcmp(a.GetUsername(), username) == 0 && a.CheckPassword(password))
            {
                return std::make_unique<domain::Admin>(a);
            }
        }

        return nullptr;
    }
}
