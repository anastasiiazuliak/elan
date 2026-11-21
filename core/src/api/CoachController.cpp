#include "elan/api/CoachController.h"

#include "elan/dtos/CoachDto.h"
#include "elan/services/CoachService.h"

#ifdef DELETE
#undef DELETE
#endif

namespace api
{
    void CoachController::RegisterRoutes(crow::SimpleApp& app)
    {
        // CREATE
        CROW_ROUTE(app, "/coaches")
        .methods(crow::HTTPMethod::POST)
        ([](const crow::request& req)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            dtos::CoachRequestDto dto;

            dto.firstName = body["firstName"].s();
            dto.lastName = body["lastName"].s();
            dto.patronymic = body["patronymic"].s();
            dto.birthDate = body["birthDate"].s();
            dto.phone = body["phone"].s();
            dto.description = body["description"].s();
            dto.password = body["password"].s();
            dto.username = body["username"].s();

            for (const auto& style : body["styleIds"])
            {
                dto.styleIds.push_back(style.i());
            }

            auto coach = dtos::FromDto(dto);

            auto coaches = storages::Coaches().GetAll();

            for (const auto& c : coaches)
            {
                if (c.GetUsername()== dto.username)
                {
                    return crow::response(400, "Username already exists");
                }
            }

            storages::Coaches().Add(coach);

            return crow::response(201, "created");
        });

        // READ ALL
        CROW_ROUTE(app, "/coaches")
        ([]()
        {
            auto all = storages::Coaches().GetAll();

            crow::json::wvalue res;

            int i = 0;

            for (const auto& coach : all)
            {
                auto dto = dtos::ToDto(coach);

                res[i]["id"] = dto.id;
                res[i]["firstName"] = dto.firstName;
                res[i]["lastName"] = dto.lastName;
                res[i]["patronymic"] = dto.patronymic;
                res[i]["birthDate"] = dto.birthDate;
                res[i]["phone"] = dto.phone;
                res[i]["description"] = dto.description;
                res[i]["username"] = dto.username;

                for (size_t j = 0; j < dto.styleIds.size(); j++)
                {
                    res[i]["styleIds"][j] = dto.styleIds[j];
                }

                i++;
            }

            return crow::response(res);
        });

        // READ ONE
        CROW_ROUTE(app, "/coaches/<int>")
        ([](int id)
        {
            auto opt = storages::Coaches().GetById(id);

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
            res["description"] = dto.description;
            res["username"] = dto.username;

            for (size_t i = 0; i < dto.styleIds.size(); i++)
            {
                res["styleIds"][i] = dto.styleIds[i];
            }

            return crow::response(res);
        });

        // UPDATE
        CROW_ROUTE(app, "/coaches/<int>")
        .methods(crow::HTTPMethod::PUT)
        ([](const crow::request& req, int id)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            auto opt = storages::Coaches().GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            dtos::CoachRequestDto dto;

            dto.firstName = body["firstName"].s();
            dto.lastName = body["lastName"].s();
            dto.patronymic = body["patronymic"].s();
            dto.birthDate = body["birthDate"].s();
            dto.phone = body["phone"].s();
            dto.description = body["description"].s();
            dto.password = body["password"].s();
            dto.username = body["username"].s();

            for (const auto& style : body["styleIds"])
            {
                dto.styleIds.push_back(style.i());
            }

            auto updated = dtos::FromDto(dto);

            auto coaches = storages::Coaches().GetAll();

            for (const auto& c : coaches)
            {
                if (c.GetId() != id && c.GetUsername() == dto.username)
                {
                    return crow::response(400, "Username already exists");
                }
            }

            storages::Coaches().Update(id, updated);

            return crow::response("updated");
        });

        // DELETE
        CROW_ROUTE(app, "/coaches/<int>")
        .methods(crow::HTTPMethod::DELETE)
        ([](int id)
        {
            storages::Coaches().Delete(id);

            return crow::response("deleted");
        });

        // ADD STYLE TO COACH
        CROW_ROUTE(app, "/coaches/<int>/styles/<int>")
        .methods(crow::HTTPMethod::POST)
        ([](int coachId, int styleId)
        {
            bool ok =
                service::CoachService::AddStyleToCoach(
                    coachId,
                    styleId);

            if (!ok)
            {
                return crow::response(
                    400,
                    "Cannot add style");
            }

            return crow::response(
                200,
                "style added");
        });

        // REMOVE STYLE FROM COACH
        CROW_ROUTE(app, "/coaches/<int>/styles/<int>")
        .methods(crow::HTTPMethod::DELETE)
        ([](int coachId, int styleId)
        {
            bool ok =
                service::CoachService::RemoveStyleFromCoach(
                    coachId,
                    styleId);

            if (!ok)
            {
                return crow::response(
                    400,
                    "Cannot remove style");
            }

            return crow::response(
                200,
                "style removed");
        });
    }
}