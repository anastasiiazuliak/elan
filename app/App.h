#pragma once

#include "elan/services/AuthService.h"
#include "elan//services/ClientService.h"
#include "elan/services/CoachService.h"
#include "elan/domain/Employee.h"
#include "elan/services/GroupService.h"
#include "elan/services/LocationService.h"
#include "elan/storage/Storage.h"
#include "elan/domain/Subscription.h"

class App
{
    static storage::Storage<domain::Subscription> subscriptions;
    static storage::Storage<domain::Client> clients;
    static storage::Storage<domain::Style> styles;
    static storage::Storage<domain::Location> locations;
    static storage::Storage<domain::Coach> coaches;
    static storage::Storage<domain::Group> groups;
    static storage::Storage<domain::Employee> employees;
    static storage::Storage<domain::Admin> admin;

    void EmployeesMenu();
    
    void CoachesMenu();
    void GroupsMenu();
    void LocationHallsMenu();
    void LocationScheduleMenu();
    void LocationsMenu();
    void StylesMenu();
    void SubscriptionsMenu();

public:
    void addTestData();
    void ShowMainMenu();
    void LoginMenu();
};
