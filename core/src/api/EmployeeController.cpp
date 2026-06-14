#include "elan/api/EmployeeController.h"

#include "elan/dtos/EmployeeDto.h"
#include "elan/storage/Storages.h"

#ifdef DELETE
#undef DELETE
#endif

namespace api
{
    void EmployeeController::RegisterRoutes(crow::SimpleApp& app)
    {
        // CREATE
        CROW_ROUTE(app, "/employees")
        .methods(crow::HTTPMethod::POST)
        ([](const crow::request& req)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            dtos::EmployeeRequestDto dto;

            dto.firstName = body["firstName"].s();
            dto.lastName = body["lastName"].s();
            dto.patronymic = body["patronymic"].s();
            dto.birthDate = body["birthDate"].s();
            dto.phone = body["phone"].s();
            dto.locationId = body["locationId"].i();
            dto.password = body["password"].s();
            dto.username = body["username"].s();

            auto employee = dtos::FromDto(dto);

            storages::Employees().Add(employee);

            return crow::response(201, "created");
        });

        // READ ALL
        CROW_ROUTE(app, "/employees")
        ([]()
        {
            auto all = storages::Employees().GetAll();

            crow::json::wvalue res;

            int i = 0;

            for (const auto& e : all)
            {
                auto dto = dtos::ToDto(e);

                res[i]["id"] = dto.id;
                res[i]["firstName"] = dto.firstName;
                res[i]["lastName"] = dto.lastName;
                res[i]["patronymic"] = dto.patronymic;
                res[i]["birthDate"] = dto.birthDate;
                res[i]["phone"] = dto.phone;
                res[i]["locationId"] = dto.locationId;
                res[i]["username"] = dto.username;

                i++;
            }

            return crow::response(res);
        });

        // READ ONE
        CROW_ROUTE(app, "/employees/<int>")
        ([](int id)
        {
            auto opt = storages::Employees().GetById(id);

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
            res["locationId"] = dto.locationId;
            res["username"] = dto.username;

            return crow::response(res);
        });

        // UPDATE
        CROW_ROUTE(app, "/employees/<int>")
        .methods(crow::HTTPMethod::PUT)
        ([](const crow::request& req, int id)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            auto opt = storages::Employees().GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            dtos::EmployeeRequestDto dto;

            dto.firstName = body["firstName"].s();
            dto.lastName = body["lastName"].s();
            dto.patronymic = body["patronymic"].s();
            dto.birthDate = body["birthDate"].s();
            dto.phone = body["phone"].s();
            dto.locationId = body["locationId"].i();
            dto.password = body["password"].s();
            dto.username = body["username"].s();

            auto updated = dtos::FromDto(dto);

            storages::Employees().Update(id, updated);

            return crow::response("updated");
        });

        // DELETE
        CROW_ROUTE(app, "/employees/<int>")
        .methods(crow::HTTPMethod::DELETE)
        ([](int id)
        {
            storages::Employees().Delete(id);

            return crow::response("deleted");
        });
    }
}