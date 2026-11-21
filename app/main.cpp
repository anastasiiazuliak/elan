#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string_view>

#include "elan/api/AuthController.h"
#include "elan/api/ClientController.h"
#include "elan/api/CoachController.h"
#include "elan/api/EmployeeController.h"
#include "elan/api/GroupController.h"
#include "elan/api/LocationController.h"
#include "elan/api/MembershipController.h"
#include "elan/api/StyleController.h"
#include "elan/api/SubscriptionController.h"
#include "elan/api/FileServer.h"
#include "elan/storage/Storages.h"

#include "crow.h"

namespace
{
    template <typename T>
    void AddDemoAccount(storage::Storage<T>& store, T account)
    {
        store.Add(account);
        if (!store.GetById(account.GetId()))
            throw std::runtime_error("Could not save demo account: " + std::string(account.GetUsername()));
    }

    void SeedDemoAccounts()
    {
        for (const auto& entry : std::filesystem::directory_iterator("data"))
        {
            if (entry.path().extension() == ".bin")
                throw std::runtime_error("Demo setup requires a data directory with no .bin files");
        }

        const common::Date birthDate(1, 1, 2000);
        constexpr auto password = "ElanDemo2026";

        try
        {
            AddDemoAccount(storages::Admins(),
                domain::Admin("Demo", "Admin", "", birthDate, "+380000000001", password, "demo-admin"));
            AddDemoAccount(storages::Employees(),
                domain::Employee("Demo", "Employee", "", birthDate, "+380000000002", 0, password, "demo-employee"));
            AddDemoAccount(storages::Coaches(),
                domain::Coach("Demo", "Coach", "", birthDate, "+380000000003", "Demo coach", password, "demo-coach"));
            AddDemoAccount(storages::Clients(),
                domain::Client("Demo", "Client", "", birthDate, "+380000000004", password, "demo-client"));
        }
        catch (...)
        {
            for (const auto* file : {
                    constants::ADMIN_FILE, constants::ADMIN_ID_FILE,
                    constants::EMPLOYEES_FILE, constants::EMPLOYEES_ID_FILE,
                    constants::COACHES_FILE, constants::COACHES_ID_FILE,
                    constants::CLIENTS_FILE, constants::CLIENTS_ID_FILE})
            {
                std::error_code ignored;
                std::filesystem::remove(file, ignored);
            }
            throw;
        }
    }
}

int main(int argc, char* argv[]) try
{
    const bool seedDemo = argc == 2 && std::string_view(argv[1]) == "--seed-demo";
    if (argc > 1 && !seedDemo)
        throw std::runtime_error("Usage: ELAN [--seed-demo]");

    namespace fs = std::filesystem;
    const auto projectRoot = fs::u8path(ELAN_PROJECT_ROOT);
    fs::current_path(projectRoot);
    fs::create_directories("data");

    if (seedDemo)
    {
        SeedDemoAccounts();
        std::cout << "Created four demo accounts.\n";
        return 0;
    }

    if (!fs::is_regular_file("frontend/pages/login.html"))
        throw std::runtime_error("Missing frontend/pages/login.html in the project directory");

    crow::SimpleApp app;

    api::AuthController::RegisterRoutes(app);
    api::ClientController::RegisterRoutes(app);
    api::CoachController::RegisterRoutes(app);
    api::EmployeeController::RegisterRoutes(app);
    api::GroupController::RegisterRoutes(app);
    api::LocationController::RegisterRoutes(app);
    api::StyleController::RegisterRoutes(app);
    api::SubscriptionController::RegisterRoutes(app);
    api::MembershipController::RegisterRoutes(app);

    CROW_ROUTE(app, "/")
    ([]()
     {
        crow::response res(302);
        res.set_header("Location", "/login");
        return res;
     });

    CROW_ROUTE(app, "/frontend/<path>")
    ([](const std::string& path)
     { return serveFile(path); });

    CROW_ROUTE(app, "/login")
    ([]()
     { return serveFile("pages/login.html"); });

    CROW_ROUTE(app, "/register")
    ([]()
     {
        crow::response res(302);
        res.set_header("Location", "/login");
        return res;
     });

    CROW_ROUTE(app, "/employee/dashboard")
    ([]()
     { return serveFile("pages/dashboard.html"); });

    CROW_ROUTE(app, "/page/dashboard")
    ([]()
     { return serveFile("pages/dashboard.html"); });

    CROW_ROUTE(app, "/page/my-trainings")
    ([]()
     { return serveFile("pages/my-groups.html"); });

    CROW_ROUTE(app, "/page/my-groups")
    ([]()
     { return serveFile("pages/my-groups.html"); });

    CROW_ROUTE(app, "/page/styles")
    ([]()
     { return serveFile("pages/styles.html"); });

    CROW_ROUTE(app, "/page/clients")
    ([]()
     { return serveFile("pages/clients.html"); });

    CROW_ROUTE(app, "/page/coaches")
    ([]()
     { return serveFile("pages/coaches.html"); });

    CROW_ROUTE(app, "/page/employees")
    ([]()
     { return serveFile("pages/employees.html"); });

    CROW_ROUTE(app, "/page/groups")
    ([]()
     { return serveFile("pages/groups.html"); });

    CROW_ROUTE(app, "/page/locations")
    ([]()
     { return serveFile("pages/locations.html"); });

    CROW_ROUTE(app, "/page/subscriptions")
    ([]()
     { return serveFile("pages/subscriptions.html"); });

    app.bindaddr("127.0.0.1")
        .port(18080)
        .multithreaded()
        .run();
}
catch (const std::exception& error)
{
    std::cerr << "ELAN: " << error.what() << '\n';
    return 1;
}
