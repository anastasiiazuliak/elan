#include <iostream>
#include "App.h"

#include "elan/api/AuthController.h"
#include "elan/api/ClientController.h"
#include "elan/api/CoachController.h"
#include "elan/api/EmployeeController.h"
#include "elan/api/GroupController.h"
#include "elan/api/LocationController.h"
#include "elan/api/StyleController.h"
#include "elan/api/SubscriptionController.h"
#include "elan/api/FileServer.h"

#include "crow.h"

int main()
{
    // Додаємо тестові дані при запуску, якщо потрібно
    //App::addTestData();

    crow::SimpleApp app;

    // =========================
    // API ROUTES
    // =========================
    /*api::AuthController::RegisterRoutes(app);
    api::ClientController::RegisterRoutes(app);
    api::CoachController::RegisterRoutes(app);
    api::EmployeeController::RegisterRoutes(app);
    api::GroupController::RegisterRoutes(app);
    api::LocationController::RegisterRoutes(app);*/
    api::StyleController::RegisterRoutes(app);
    api::SubscriptionController::RegisterRoutes(app);

    // =========================
    // FRONTEND
    // =========================

    CROW_ROUTE(app, "/")
    ([]() {
        crow::response res(302);
        res.set_header("Location", "/page/styles");
        return res;
    });

    CROW_ROUTE(app, "/frontend/<path>")
    ([](std::string path) {
        return serveFile("../frontend/" + path);
    });

    // окремі сторінки
    CROW_ROUTE(app, "/page/styles")
    ([]() {
        return serveFile("../frontend/pages/styles.html");
    });

    CROW_ROUTE(app, "/page/clients")
    ([]() {
        return serveFile("../frontend/pages/clients.html");
    });

    CROW_ROUTE(app, "/page/coaches")
    ([]() {
        return serveFile("../frontend/pages/coaches.html");
    });

    CROW_ROUTE(app, "/page/employees")
    ([]() {
        return serveFile("../frontend/pages/employees.html");
    });

    CROW_ROUTE(app, "/page/groups")
    ([]() {
        return serveFile("../frontend/pages/groups.html");
    });

    CROW_ROUTE(app, "/page/locations")
    ([]() {
        return serveFile("../frontend/pages/locations.html");
    });

    CROW_ROUTE(app, "/page/subscriptions")
    ([]() {
        return serveFile("../frontend/pages/subscriptions.html");
    });

    app.port(18080)
       .multithreaded()
       .run();
}