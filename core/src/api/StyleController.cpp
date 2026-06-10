#include "elan/api/StyleController.h"

#include "elan/dtos/StyleDto.h"
#include "elan/api/FileServer.h"
#include "elan/storage/Storages.h"

#ifdef DELETE
#undef DELETE
#endif

namespace api
{
    void StyleController::RegisterRoutes(crow::SimpleApp &app)
    {
        // CREATE
        CROW_ROUTE(app, "/styles").methods(crow::HTTPMethod::POST)([](const crow::request &req)
                                                                   {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            dtos::StyleDto dto;
            dto.name = body["name"].s();
            dto.description = body["description"].s();

            auto domainObj = dtos::FromDto(dto);

            storages::Styles().Add(domainObj);

            return crow::response(201, "created"); });

        // READ ALL
        CROW_ROUTE(app, "/styles")
        ([]()
         {
            auto all = storages::Styles().GetAll();

            crow::json::wvalue res;

            int i = 0;
            for (const auto& s : all)
            {
                auto dto = dtos::ToDto(s);

                res[i]["id"] = dto.id;
                res[i]["name"] = dto.name;
                res[i]["description"] = dto.description;

                i++;
            }

            return crow::response(res); });

        // READ ONE
        CROW_ROUTE(app, "/styles/<int>")
        ([](int id)
         {
            auto opt = storages::Styles().GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            auto dto = dtos::ToDto(opt.value());

            crow::json::wvalue res;
            res["id"] = dto.id;
            res["name"] = dto.name;
            res["description"] = dto.description;

            return crow::response(res); });

        // UPDATE
        CROW_ROUTE(app, "/styles/<int>").methods(crow::HTTPMethod::PUT)([](const crow::request &req, int id)
                                                                        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            auto opt = storages::Styles().GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            dtos::StyleDto dto;
            dto.id = id;
            dto.name = body["name"].s();
            dto.description = body["description"].s();

            auto updated = dtos::FromDto(dto);

            storages::Styles().Update(id, updated);

            return crow::response("updated"); });

        // DELETE
        CROW_ROUTE(app, "/styles/<int>").methods(crow::HTTPMethod::DELETE)([&](int id)
                                                                           {
            storages::Styles().Delete(id);
            return crow::response("deleted"); });
    }
}
