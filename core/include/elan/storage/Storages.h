#pragma once
#include "elan/storage/Storage.h"
#include "elan/domain/Admin.h"
#include "elan/domain/Client.h"
#include "elan/domain/Coach.h"
#include "elan/domain/Employee.h"
#include "elan/domain/Group.h"
#include "elan/domain/Location.h"
#include "elan/domain/Subscription.h"
#include "elan/domain/Style.h"
#include "elan/common/constants.h"

namespace storages
{
    inline storage::Storage<domain::Client>& Clients() {
        static storage::Storage<domain::Client> s(
            constants::CLIENTS_FILE, constants::CLIENTS_ID_FILE);
        return s;
    }

    inline storage::Storage<domain::Coach>& Coaches() {
        static storage::Storage<domain::Coach> s(
            constants::COACHES_FILE, constants::COACHES_ID_FILE);
        return s;
    }

    inline storage::Storage<domain::Employee>& Employees() {
        static storage::Storage<domain::Employee> s(
            constants::EMPLOYEES_FILE, constants::EMPLOYEES_ID_FILE);
        return s;
    }

    inline storage::Storage<domain::Location>& Locations() {
        static storage::Storage<domain::Location> s(
            constants::LOCATIONS_FILE, constants::LOCATIONS_ID_FILE);
        return s;
    }

    inline storage::Storage<domain::Group>& Groups() {
        static storage::Storage<domain::Group> s(
            constants::GROUPS_FILE, constants::GROUPS_ID_FILE);
        return s;
    }

    inline storage::Storage<domain::Subscription>& Subscriptions() {
        static storage::Storage<domain::Subscription> s(
            constants::SUBSCRIPTIONS_FILE, constants::SUBSCRIPTIONS_ID_FILE);
        return s;
    }

    inline storage::Storage<domain::Style>& Styles() {
        static storage::Storage<domain::Style> s(
            constants::STYLES_FILE, constants::STYLES_ID_FILE);
        return s;
    }

    inline storage::Storage<domain::Admin>& Admins() {
        static storage::Storage<domain::Admin> s(
            constants::ADMIN_FILE, constants::ADMIN_ID_FILE);
        return s;
    }
}