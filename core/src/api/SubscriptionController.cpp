#include "elan/api/SubscriptionController.h"
#include "elan/dtos/SubscriptionDto.h"

#ifdef DELETE
#undef DELETE
#endif

namespace api
{
    storage::Storage<domain::Subscription> SubscriptionController::subscriptions(
        constants::SUBSCRIPTIONS_FILE,
        constants::SUBSCRIPTIONS_ID_FILE
    );

    void SubscriptionController::RegisterRoutes(crow::SimpleApp &app)
    {
        // CREATE
        CROW_ROUTE(app, "/subscriptions").methods(crow::HTTPMethod::POST)
        ([](const crow::request &req)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            dtos::SubscriptionDto dto;

            dto.name = body["name"].s();

            dto.category = static_cast<common::Category>(
                body["category"].i()
            );

            dto.duration = body["duration"].i();
            dto.numberOfWorkouts = body["numberOfWorkouts"].i();

            auto domainObj = dtos::FromDto(dto);

            subscriptions.Add(domainObj);

            return crow::response(201, "created");
        });

        // READ ALL
        CROW_ROUTE(app, "/subscriptions")
        ([]()
        {
            auto all = subscriptions.GetAll();

            crow::json::wvalue res;

            int i = 0;

            for (const auto& s : all)
            {
                auto dto = dtos::ToDto(s);

                res[i]["id"] = dto.id;
                res[i]["name"] = dto.name;
                res[i]["category"] = static_cast<int>(dto.category);
                res[i]["duration"] = dto.duration;
                res[i]["numberOfWorkouts"] = dto.numberOfWorkouts;

                i++;
            }

            return crow::response(res);
        });

        // READ ONE
        CROW_ROUTE(app, "/subscriptions/<int>")
        ([](int id)
        {
            auto opt = subscriptions.GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            auto dto = dtos::ToDto(opt.value());

            crow::json::wvalue res;

            res["id"] = dto.id;
            res["name"] = dto.name;
            res["category"] = static_cast<int>(dto.category);
            res["duration"] = dto.duration;
            res["numberOfWorkouts"] = dto.numberOfWorkouts;

            return crow::response(res);
        });

        // UPDATE
        CROW_ROUTE(app, "/subscriptions/<int>")
        .methods(crow::HTTPMethod::PUT)
        ([](const crow::request &req, int id)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            auto opt = subscriptions.GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            dtos::SubscriptionDto dto;

            dto.id = id;
            dto.name = body["name"].s();

            dto.category = static_cast<common::Category>(
                body["category"].i()
            );

            dto.duration = body["duration"].i();
            dto.numberOfWorkouts = body["numberOfWorkouts"].i();

            auto updated = dtos::FromDto(dto);

            subscriptions.Update(id, updated);

            return crow::response("updated");
        });

        // DELETE
        CROW_ROUTE(app, "/subscriptions/<int>")
        .methods(crow::HTTPMethod::DELETE)
        ([](int id)
        {
            subscriptions.Delete(id);

            return crow::response("deleted");
        });
    }
}
