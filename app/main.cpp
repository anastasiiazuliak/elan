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
    crow::SimpleApp app;

    // API
    api::ClientController::RegisterRoutes(app);
    api::StyleController::RegisterRoutes(app);

    // FRONTEND
    CROW_ROUTE(app, "/")
    ([](){
        return serveFile("frontend/pages/styles.html");
    });

    CROW_ROUTE(app, "/frontend/<path>")
    ([](std::string path){
        return serveFile("../frontend/" + path);
    });

    app.port(18080).run();
}