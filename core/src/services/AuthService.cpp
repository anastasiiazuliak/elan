#include <cstring>

#include "elan/services/AuthService.h"

namespace service
{
    storage::Storage<domain::Employee> AuthService::employees(
        "../data/employees.bin",
        "../data/employees_id.bin");

    storage::Storage<domain::Coach> AuthService::coaches(
        "../data/coaches.bin",
        "../data/coaches_id.bin");

    storage::Storage<domain::Client> AuthService::clients(
        "../data/clients.bin",
        "../data/clients_id.bin");
        
    storage::Storage<domain::Admin> AuthService::admin(
        "../data/admin.bin",
        "../data/admin_id.bin");

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
