#pragma once

#include <memory>

#include "elan/domain/Client.h"
#include "elan/domain/Coach.h"
#include "elan/domain/Employee.h"
#include "elan/domain/Admin.h"
#include "elan/storage/Storage.h"

namespace service
{
    class AuthService
    {
        static storage::Storage<domain::Client> clients;
        static storage::Storage<domain::Coach> coaches;
        static storage::Storage<domain::Employee> employees;
        static storage::Storage<domain::Admin> admin;

    public:
        static std::unique_ptr<domain::Person>
        Login(const char *username, const char *password);
    };
}