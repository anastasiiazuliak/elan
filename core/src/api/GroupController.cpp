#include "elan/api/GroupController.h"

#include "elan/dtos/GroupDto.h"

#ifdef DELETE
#undef DELETE
#endif

namespace api
{
    void GroupController::RegisterRoutes(crow::SimpleApp &app)
    {
        // CREATE
        CROW_ROUTE(app, "/groups").methods(crow::HTTPMethod::POST)
        ([](const crow::request &req)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            dtos::GroupDto dto;

            dto.name = body["name"].s();
            dto.coachId = body["coachId"].i();
            dto.styleId = body["styleId"].i();
            dto.skillLevel = static_cast<domain::SkillLevel>(
            body["skillLevel"].i());
            dto.category = static_cast<common::Category>(body["category"].i());

            for (const auto& subscription : body["subscriptionIds"])
            {
                dto.subscriptionIds.push_back(subscription.i());
            }

            auto domainObj = dtos::FromDto(dto);

            storages::Groups().Add(domainObj);

            return crow::response(201, "created");
        });

        // READ ALL
        CROW_ROUTE(app, "/groups")
        ([]()
        {
            auto all = storages::Groups().GetAll();

            crow::json::wvalue res;

            int i = 0;

            for (const auto& g : all)
            {
                auto dto = dtos::ToDto(g);

                res[i]["id"] = dto.id;
                res[i]["name"] = dto.name;
                res[i]["coachId"] = dto.coachId;
                res[i]["styleId"] = dto.styleId;
                res[i]["skillLevel"] = static_cast<int>(dto.skillLevel);
                res[i]["category"] = static_cast<int>(dto.category);
                res[i]["subscriptionCount"] = dto.subscriptionCount;

                for (size_t j = 0; j < dto.subscriptionIds.size(); j++)
                {
                    res[i]["subscriptionIds"][j] = dto.subscriptionIds[j];
                }

                i++;
            }

            return crow::response(res);
        });

        // READ ONE
        CROW_ROUTE(app, "/groups/<int>")
        ([](int id)
        {
            auto opt = storages::Groups().GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            auto dto = dtos::ToDto(opt.value());

            crow::json::wvalue res;

            res["id"] = dto.id;
            res["name"] = dto.name;
            res["coachId"] = dto.coachId;
            res["styleId"] = dto.styleId;
            res["skillLevel"] = static_cast<int>(dto.skillLevel);
            res["category"] = static_cast<int>(dto.category);
            res["subscriptionCount"] = dto.subscriptionCount;

            for (size_t i = 0; i < dto.subscriptionIds.size(); i++)
            {
                res["subscriptionIds"][i] = dto.subscriptionIds[i];
            }

            return crow::response(res);
        });

        // UPDATE
        CROW_ROUTE(app, "/groups/<int>")
        .methods(crow::HTTPMethod::PUT)
        ([](const crow::request &req, int id)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            auto opt = storages::Groups().GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            dtos::GroupDto dto;

            dto.id = id;
            dto.name = body["name"].s();
            dto.coachId = body["coachId"].i();
            dto.styleId = body["styleId"].i();
            dto.skillLevel =
                static_cast<domain::SkillLevel>(
                    body["skillLevel"].i());
            dto.category = static_cast<common::Category>(body["category"].i());

            for (const auto& subscription : body["subscriptionIds"])
            {
                dto.subscriptionIds.push_back(subscription.i());
            }

            auto updated = dtos::FromDto(dto);

            storages::Groups().Update(id, updated);

            return crow::response("updated");
        });

        // DELETE
        CROW_ROUTE(app, "/groups/<int>")
        .methods(crow::HTTPMethod::DELETE)
        ([](int id)
        {
            storages::Groups().Delete(id);

            return crow::response("deleted");
        });

        // GET GROUPS BY COACH
        CROW_ROUTE(app, "/coaches/<int>/groups")
        ([](int coachId)
        {
            auto coachGroups = service::GroupService::GetGroupsByCoachId(coachId);

            crow::json::wvalue res;

            int i = 0;

            for (const auto& g : coachGroups)
            {
                auto dto = dtos::ToDto(g);

                res[i]["id"] = dto.id;
                res[i]["name"] = dto.name;
                res[i]["coachId"] = dto.coachId;
                res[i]["styleId"] = dto.styleId;
                res[i]["skillLevel"] = static_cast<int>(dto.skillLevel);
                res[i]["category"] = static_cast<int>(dto.category);
                res[i]["subscriptionCount"] = dto.subscriptionCount;

                for (size_t j = 0; j < dto.subscriptionIds.size(); j++)
                {
                    res[i]["subscriptionIds"][j] = dto.subscriptionIds[j];
                }

                i++;
            }

            return crow::response(res);
        });

        // SCHEDULE FOR GROUP
        CROW_ROUTE(app, "/groups/<int>/schedule")
        ([](int groupId)
        {
            auto schedule = service::GroupService::GetScheduleByGroup(groupId);

            crow::json::wvalue res;

            for (size_t i = 0; i < schedule.size(); i++)
            {
                res[i]["groupId"] = schedule[i].groupId;
                res[i]["hallId"] = schedule[i].hallId;
                res[i]["day"] = static_cast<int>(schedule[i].day);
                res[i]["time"] = static_cast<int>(schedule[i].time);
            }

            return crow::response(res);
        });
    }
}
