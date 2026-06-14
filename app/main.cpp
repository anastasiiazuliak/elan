#include <iostream>

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

int main()
{
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
    ([](std::string path)
     { return serveFile("../frontend/" + path); });

    CROW_ROUTE(app, "/login")
    ([]()
     { return serveFile("../frontend/pages/login.html"); });

    CROW_ROUTE(app, "/register")
    ([]()
     {
        crow::response res(302);
        res.set_header("Location", "/login");
        return res;
     });

    CROW_ROUTE(app, "/employee/dashboard")
    ([]()
     { return serveFile("../frontend/pages/dashboard.html"); });

    CROW_ROUTE(app, "/page/dashboard")
    ([]()
     { return serveFile("../frontend/pages/dashboard.html"); });

    CROW_ROUTE(app, "/page/styles")
    ([]()
     { return serveFile("../frontend/pages/styles.html"); });

    CROW_ROUTE(app, "/page/clients")
    ([]()
     { return serveFile("../frontend/pages/clients.html"); });

    CROW_ROUTE(app, "/page/coaches")
    ([]()
     { return serveFile("../frontend/pages/coaches.html"); });

    CROW_ROUTE(app, "/page/employees")
    ([]()
     { return serveFile("../frontend/pages/employees.html"); });

    CROW_ROUTE(app, "/page/groups")
    ([]()
     { return serveFile("../frontend/pages/groups.html"); });

    CROW_ROUTE(app, "/page/locations")
    ([]()
     { return serveFile("../frontend/pages/locations.html"); });

    CROW_ROUTE(app, "/page/subscriptions")
    ([]()
     { return serveFile("../frontend/pages/subscriptions.html"); });

    app.port(18080)
        .multithreaded()
        .run();
}
