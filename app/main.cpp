#include <filesystem>
#include <iostream>
#include <stdexcept>

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

#include "crow.h"

int main() try
{
    namespace fs = std::filesystem;
    const auto projectRoot = fs::u8path(ELAN_PROJECT_ROOT);
    fs::current_path(projectRoot);
    if (!fs::is_regular_file("frontend/pages/login.html"))
        throw std::runtime_error("Missing frontend/pages/login.html in the project directory");
    fs::create_directories("data");

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
    std::cerr << "ELAN could not start on http://127.0.0.1:18080: " << error.what() << '\n';
    return 1;
}
