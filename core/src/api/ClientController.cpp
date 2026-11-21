#include "elan/api/ClientController.h"

#include "elan/dtos/ClientDto.h"
#include "elan/storage/Storages.h"

#ifdef DELETE
#undef DELETE
#endif


namespace api
{
    void ClientController::RegisterRoutes(crow::SimpleApp& app)
    {
        // CREATE
        CROW_ROUTE(app, "/clients")
        .methods(crow::HTTPMethod::POST)
        ([](const crow::request& req)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            dtos::ClientRequestDto dto;

            dto.firstName = body["firstName"].s();
            dto.lastName = body["lastName"].s();
            dto.patronymic = body["patronymic"].s();
            dto.birthDate = body["birthDate"].s();
            dto.phone = body["phone"].s();
            dto.username = body["username"].s();
            dto.password = body["password"].s();

            auto client = dtos::FromDto(dto);

            auto clients = storages::Clients().GetAll();

            for (const auto& c : clients)
            {
                if (c.GetUsername() == dto.username)
                {
                    return crow::response(400, "Username already exists");
                }
            }

            storages::Clients().Add(client);

            return crow::response(201, "created");
        });

        // READ ALL
        CROW_ROUTE(app, "/clients")
        ([]()
        {
            auto all = storages::Clients().GetAll();

            crow::json::wvalue res;

            int i = 0;

            for (const auto& c : all)
            {
                auto dto = dtos::ToDto(c);

                res[i]["id"] = dto.id;
                res[i]["firstName"] = dto.firstName;
                res[i]["lastName"] = dto.lastName;
                res[i]["patronymic"] = dto.patronymic;
                res[i]["birthDate"] = dto.birthDate;
                res[i]["phone"] = dto.phone;
                res[i]["username"] = dto.username;
                res[i]["category"] = static_cast<int>(dto.category);

                i++;
            }

            return crow::response(res);
        });

        // READ ONE
        CROW_ROUTE(app, "/clients/<int>")
        ([](int id)
        {
            auto opt = storages::Clients().GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            auto dto = dtos::ToDto(opt.value());

            crow::json::wvalue res;

            res["id"] = dto.id;
            res["firstName"] = dto.firstName;
            res["lastName"] = dto.lastName;
            res["patronymic"] = dto.patronymic;
            res["birthDate"] = dto.birthDate;
            res["phone"] = dto.phone;
            res["username"] = dto.username;
            res["category"] = static_cast<int>(dto.category);

            return crow::response(res);
        });

        // UPDATE
        CROW_ROUTE(app, "/clients/<int>")
        .methods(crow::HTTPMethod::PUT)
        ([](const crow::request& req, int id)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            auto opt = storages::Clients().GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            dtos::ClientRequestDto dto;

            dto.firstName = body["firstName"].s();
            dto.lastName = body["lastName"].s();
            dto.patronymic = body["patronymic"].s();
            dto.birthDate = body["birthDate"].s();
            dto.phone = body["phone"].s();
            dto.username = body["username"].s();
            dto.password = body["password"].s();

            auto updated = dtos::FromDto(dto);

            auto clients = storages::Clients().GetAll();

            for (const auto& c : clients)
            {
                if (c.GetId() != id && c.GetUsername() == dto.username)
                {
                    return crow::response(400, "Username already exists");
                }
            }

            storages::Clients().Update(id, updated);

            return crow::response("updated");
        });

        // DELETE
        CROW_ROUTE(app, "/clients/<int>")
        .methods(crow::HTTPMethod::DELETE)
        ([](int id)
        {
            storages::Clients().Delete(id);

            return crow::response("deleted");
        });
    }
}