#include "elan/api/LocationController.h"

#include "elan/dtos/LocationDto.h"
#include "elan/dtos/ScheduleDto.h"
#include "elan/dtos/HallDto.h"

#include "elan/services/LocationService.h"

#ifdef DELETE
#undef DELETE
#endif

namespace api
{
    void LocationController::RegisterRoutes(crow::SimpleApp &app)
    {
        // =========================================================
        // LOCATIONS
        // =========================================================

        // CREATE
        CROW_ROUTE(app, "/locations")
        .methods(crow::HTTPMethod::POST)([](const crow::request &req)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, crow::json::wvalue{{"message","Invalid JSON"}});

            dtos::LocationDto dto;
            dto.address = body["address"].s();

            auto location = dtos::FromDto(dto);
            storages::Locations().Add(location);

            return crow::response(201, crow::json::wvalue{
                {"message", "created"}
            });
        });

        // READ ALL
        CROW_ROUTE(app, "/locations")
        ([]()
        {
            auto all = storages::Locations().GetAll();

            crow::json::wvalue res;

            int i = 0;
            for (const auto& l : all)
            {
                auto dto = dtos::ToDto(l);

                res[i]["id"] = dto.id;
                res[i]["address"] = dto.address;

                auto halls = l.GetHalls();

                for(size_t j = 0; j < halls.size(); j++)
                {
                    res[i]["halls"][j]["id"] = halls[j].id;
                    res[i]["halls"][j]["name"] = halls[j].name;
                    res[i]["halls"][j]["capacity"] = halls[j].capacity;
                    res[i]["halls"][j]["type"] = (int)halls[j].type;
                }

                i++;
            }

            return crow::response(crow::json::wvalue{
                {"data", res}
            });
        });

        // READ ONE
        CROW_ROUTE(app, "/locations/<int>")
        ([](int id)
        {
            auto opt = storages::Locations().GetById(id);

            if (!opt)
                return crow::response(404, crow::json::wvalue{{"message","Not found"}});

            auto dto = dtos::ToDto(opt.value());

            crow::json::wvalue res;
            res["id"] = dto.id;
            res["address"] = dto.address;

            return crow::response(crow::json::wvalue{
                {"data", res}
            });
        });

        // UPDATE
        CROW_ROUTE(app, "/locations/<int>")
        .methods(crow::HTTPMethod::PUT)([](const crow::request &req, int id)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, crow::json::wvalue{{"message","Invalid JSON"}});

            auto opt = storages::Locations().GetById(id);

            if (!opt)
                return crow::response(404, crow::json::wvalue{{"message","Not found"}});

            auto location = opt.value();
            std::string address = body["address"].s();

            location.SetAddress(address.c_str());
            storages::Locations().Update(id, location);

            return crow::response(200, crow::json::wvalue{
                {"message", "updated"}
            });
        });

        // DELETE
        CROW_ROUTE(app, "/locations/<int>")
        .methods(crow::HTTPMethod::DELETE)([](int id)
        {
            storages::Locations().Delete(id);

            return crow::response(200, crow::json::wvalue{
                {"message", "deleted"}
            });
        });

        // =========================================================
        // HALLS
        // =========================================================

        // ADD HALL
        CROW_ROUTE(app, "/locations/<int>/halls")
        .methods(crow::HTTPMethod::POST)([](const crow::request &req, int locationId)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, crow::json::wvalue{{"message","Invalid JSON"}});

            dtos::HallDto dto;
            dto.name = body["name"].s();
            dto.capacity = body["capacity"].i();

            auto hall = dtos::FromDto(dto);

            bool ok = service::LocationService::AddHall(locationId, hall);

            if (!ok)
                return crow::response(400, crow::json::wvalue{{"message","Cannot add hall"}});

            return crow::response(201, crow::json::wvalue{
                {"message", "hall added"}
            });
        });

        // REMOVE HALL
        CROW_ROUTE(app, "/locations/<int>/halls/<int>")
        .methods(crow::HTTPMethod::DELETE)([](int locationId, int hallId)
        {
            bool ok = service::LocationService::RemoveHall(locationId, hallId);

            if (!ok)
                return crow::response(400, crow::json::wvalue{{"message","Cannot remove hall"}});

            return crow::response(200, crow::json::wvalue{
                {"message", "hall removed"}
            });
        });

        // UPDATE HALL
        CROW_ROUTE(app, "/locations/<int>/halls/<int>")
        .methods(crow::HTTPMethod::PUT)([](const crow::request& req, int locationId, int hallId)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, crow::json::wvalue{{"message","Invalid JSON"}});

            if (!body.has("capacity"))
                return crow::response(400, crow::json::wvalue{{"message","Missing capacity"}});

            std::string name = body["name"].s();
            int capacity = body["capacity"].i();

            bool ok = service::LocationService::UpdateHall(
                locationId,
                hallId,
                name.c_str(),
                capacity
            );

            if (!ok)
                return crow::response(400, crow::json::wvalue{{"message","Cannot update hall"}});

            return crow::response(200, crow::json::wvalue{
                {"message", "hall updated"}
            });
        });

        // READ ALL HALLS
        CROW_ROUTE(app, "/locations/<int>/halls")
        ([](int locationId)
        {
            auto opt = storages::Locations().GetById(locationId);

            if (!opt)
                return crow::response(404, crow::json::wvalue{{"message","Location not found"}});

            auto location = opt.value();
            auto halls = location.GetHalls();

            crow::json::wvalue res;

            for (size_t i = 0; i < halls.size(); i++)
            {
                res[i]["id"] = halls[i].id;
                res[i]["name"] = halls[i].name;
                res[i]["capacity"] = halls[i].capacity;
                res[i]["type"] = static_cast<int>(halls[i].type);
            }

            return crow::response(crow::json::wvalue{
                {"data", res}
            });
        });

        // READ ONE HALL
        CROW_ROUTE(app, "/locations/<int>/halls/<int>")
        ([](int locationId, int hallId)
        {
            auto opt = storages::Locations().GetById(locationId);

            if (!opt)
                return crow::response(404, crow::json::wvalue{{"message","Location not found"}});

            auto location = opt.value();
            const domain::Hall* hall = location.GetHallById(hallId);

            if (!hall)
                return crow::response(404, crow::json::wvalue{{"message","Hall not found"}});

            crow::json::wvalue res;
            res["id"] = hall->id;
            res["name"] = hall->name;
            res["capacity"] = hall->capacity;
            res["type"] = static_cast<int>(hall->type);

            return crow::response(crow::json::wvalue{
                {"data", res}
            });
        });

        // =========================================================
        // SCHEDULE
        // =========================================================

        // ADD SCHEDULE
        CROW_ROUTE(app, "/locations/<int>/schedule")
        .methods(crow::HTTPMethod::POST)([](const crow::request &req, int locationId)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, crow::json::wvalue{{"message","Invalid JSON"}});

            dtos::ScheduleDto dto;
            dto.groupId = body["groupId"].i();
            dto.hallId = body["hallId"].i();
            dto.day = body["day"].i();
            dto.time = body["time"].i();
            dto.isOccupied = body["isOccupied"].b();

            auto schedule = dtos::FromDto(dto);

            bool ok = service::LocationService::AddSchedule(locationId, schedule);

            if (!ok)
                return crow::response(400, crow::json::wvalue{{"message","Cannot add schedule"}});

            return crow::response(201, crow::json::wvalue{
                {"message", "schedule added"}
            });
        });

        // REMOVE SCHEDULE
        CROW_ROUTE(app, "/locations/<int>/schedule")
        .methods(crow::HTTPMethod::DELETE)([](const crow::request &req, int locationId)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, crow::json::wvalue{{"message","Invalid JSON"}});

            dtos::ScheduleDto dto;
            dto.groupId = body["groupId"].i();
            dto.hallId = body["hallId"].i();
            dto.day = body["day"].i();
            dto.time = body["time"].i();

            auto schedule = dtos::FromDto(dto);

            bool ok = service::LocationService::RemoveSchedule(locationId, schedule);

            if (!ok)
                return crow::response(400, crow::json::wvalue{{"message","Cannot remove schedule"}});

            return crow::response(200, crow::json::wvalue{
                {"message", "schedule removed"}
            });
        });

        // READ SCHEDULE
        CROW_ROUTE(app, "/locations/<int>/schedule")
        ([](const crow::request& req, int locationId)
        {
            std::vector<domain::Schedule> result;
            auto dayParam = req.url_params.get("day");

            if (dayParam)
            {
                int dayInt = std::stoi(dayParam);
                result = service::LocationService::GetScheduleByDay(
                    locationId,
                    static_cast<domain::Day>(dayInt)
                );
            }
            else
            {
                auto opt = storages::Locations().GetById(locationId);
                if (!opt)
                    return crow::response(404, crow::json::wvalue{{"message","Location not found"}});

                result = opt.value().GetScheduleList();
            }

            crow::json::wvalue res;

            for (size_t i = 0; i < result.size(); i++)
            {
                res[i]["groupId"] = result[i].groupId;
                res[i]["hallId"] = result[i].hallId;
                res[i]["day"] = static_cast<int>(result[i].day);
                res[i]["time"] = static_cast<int>(result[i].time);
            }

            return crow::response(crow::json::wvalue{
                {"data", res}
            });
        });

        // SCHEDULE BY HALL
        CROW_ROUTE(app, "/locations/<int>/halls/<int>/schedule")
        ([](int locationId, int hallId)
        {
            auto schedule = service::LocationService::GetScheduleByHall(locationId, hallId);

            crow::json::wvalue res;

            for (size_t i = 0; i < schedule.size(); i++)
            {
                res[i]["groupId"] = schedule[i].groupId;
                res[i]["hallId"] = schedule[i].hallId;
                res[i]["day"] = static_cast<int>(schedule[i].day);
                res[i]["time"] = static_cast<int>(schedule[i].time);
            }

            return crow::response(crow::json::wvalue{
                {"data", res}
            });
        });
    }
}