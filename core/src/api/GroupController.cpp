#include "elan/api/GroupController.h"
#include "elan/dtos/GroupDto.h"

#ifdef DELETE
#undef DELETE
#endif

namespace api
{
    storage::Storage<domain::Group> GroupController::groups(
        constants::GROUPS_FILE,
        constants::GROUPS_ID_FILE
    );

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

            dto.coachId = body["coachId"].i();
            dto.styleId = body["styleId"].i();

            dto.skillLevel =
                static_cast<domain::SkillLevel>(
                    body["skillLevel"].i()
                );

            auto domainObj = dtos::FromDto(dto);

            groups.Add(domainObj);

            return crow::response(201, "created");
        });

        // READ ALL
        CROW_ROUTE(app, "/groups")
        ([]()
        {
            auto all = groups.GetAll();

            crow::json::wvalue res;

            int i = 0;

            for (const auto& g : all)
            {
                auto dto = dtos::ToDto(g);

                res[i]["id"] = dto.id;
                res[i]["coachId"] = dto.coachId;
                res[i]["styleId"] = dto.styleId;

                res[i]["skillLevel"] =
                    static_cast<int>(dto.skillLevel);

                res[i]["clientCount"] = dto.clientCount;

                i++;
            }

            return crow::response(res);
        });

        // READ ONE
        CROW_ROUTE(app, "/groups/<int>")
        ([](int id)
        {
            auto opt = groups.GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            auto dto = dtos::ToDto(opt.value());

            crow::json::wvalue res;

            res["id"] = dto.id;
            res["coachId"] = dto.coachId;
            res["styleId"] = dto.styleId;

            res["skillLevel"] =
                static_cast<int>(dto.skillLevel);

            res["clientCount"] = dto.clientCount;

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

            auto opt = groups.GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            dtos::GroupDto dto;

            dto.id = id;

            dto.coachId = body["coachId"].i();
            dto.styleId = body["styleId"].i();

            dto.skillLevel =
                static_cast<domain::SkillLevel>(
                    body["skillLevel"].i()
                );

            auto updated = dtos::FromDto(dto);

            groups.Update(id, updated);

            return crow::response("updated");
        });

        // DELETE
        CROW_ROUTE(app, "/groups/<int>")
        .methods(crow::HTTPMethod::DELETE)
        ([](int id)
        {
            groups.Delete(id);

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
                res[i]["coachId"] = dto.coachId;
                res[i]["styleId"] = dto.styleId;

                res[i]["skillLevel"] =
                    static_cast<int>(dto.skillLevel);

                res[i]["clientCount"] = dto.clientCount;

                i++;
            }

            return crow::response(res);
        });

        // ADD CLIENT TO GROUP
        CROW_ROUTE(app, "/groups/<int>/clients/<int>")
        .methods(crow::HTTPMethod::POST)
        ([](int groupId, int clientId)
        {
            bool ok = service::GroupService::AddClientToGroup( groupId, clientId);

            if (!ok)
            {
                return crow::response( 400, "Cannot add client");
            }

            return crow::response(200, "client added");
        });

        // REMOVE CLIENT FROM GROUP
        CROW_ROUTE(app, "/groups/<int>/clients/<int>")
        .methods(crow::HTTPMethod::DELETE)
        ([](int groupId, int clientId)
        {
            bool ok = service::GroupService::RemoveClientFromGroup(groupId, clientId);

            if (!ok)
            {
                return crow::response(400, "Cannot remove client");
            }

            return crow::response(200, "client removed");
        });
    }
}