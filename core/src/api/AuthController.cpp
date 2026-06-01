#include "elan/api/AuthController.h"
#include "elan/services/AuthService.h"

#ifdef DELETE
#undef DELETE
#endif

namespace api
{
    void AuthController::RegisterRoutes(crow::SimpleApp& app)
    {
        // LOGIN
        CROW_ROUTE(app, "/auth/login")
        .methods(crow::HTTPMethod::POST)
        ([](const crow::request& req)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            const char* username = body["username"].s();
            const char* password = body["password"].s();

            auto result = service::AuthService::Login(username, password);

            if (!result.has_value())
            {
                return crow::response(401, "Invalid credentials");
            }

            crow::json::wvalue res;

            res["id"] = result->id;
            res["username"] = result->username;
            res["role"] = static_cast<int>(result->role);

            return crow::response(res);
        });

        // LOGOUT
        CROW_ROUTE(app, "/auth/logout")
        .methods(crow::HTTPMethod::POST)
        ([](const crow::request& req)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            int userId = body["userId"].i();

            service::AuthService::Logout(userId);

            return crow::response(200, "logged out");
        });
    }
}