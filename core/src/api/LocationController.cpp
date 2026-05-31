#include "elan/api/LocationController.h"

#include "elan/dtos/LocationDto.h"
#include "elan/dtos/HallDto.h"
#include "elan/dtos/ScheduleDto.h"

#include "elan/services/LocationService.h"

#ifdef DELETE
#undef DELETE
#endif

namespace api
{
    storage::Storage<domain::Location> LocationController::locations(
        constants::LOCATIONS_FILE,
        constants::LOCATIONS_ID_FILE);

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
                return crow::response(400, "Invalid JSON");

            dtos::LocationDto dto;

            dto.address = body["address"].s();

            auto location = dtos::FromDto(dto);

            locations.Add(location);

            return crow::response(201, "created"); });

        // READ ALL
        CROW_ROUTE(app, "/locations")
        ([]()
         {
            auto all = locations.GetAll();

            crow::json::wvalue res;

            int i = 0;

            for (const auto& l : all)
            {
                auto dto = dtos::ToDto(l);

                res[i]["id"] = dto.id;
                res[i]["address"] = dto.address;

                i++;
            }

            return crow::response(res); });

        // READ ONE
        CROW_ROUTE(app, "/locations/<int>")
        ([](int id)
         {
            auto opt = locations.GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            auto dto = dtos::ToDto(opt.value());

            crow::json::wvalue res;

            res["id"] = dto.id;
            res["address"] = dto.address;

            return crow::response(res); });

        // UPDATE
        CROW_ROUTE(app, "/locations/<int>")
            .methods(crow::HTTPMethod::PUT)([](const crow::request &req, int id)
            {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            auto opt = locations.GetById(id);

            if (!opt)
                return crow::response(404, "Not found");

            auto location = opt.value();

            std::string address = body["address"].s();
            location.SetAddress(address.c_str());

            locations.Update(id, location);

            return crow::response("updated"); });

        // DELETE
        CROW_ROUTE(app, "/locations/<int>")
            .methods(crow::HTTPMethod::DELETE)([](int id)
            {
            locations.Delete(id);

            return crow::response("deleted"); });

        // =========================================================
        // HALLS
        // =========================================================

         // ADD HALL
        CROW_ROUTE(app, "/locations/<int>/halls")
        .methods(crow::HTTPMethod::POST)
        ([](const crow::request &req, int locationId)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400);

            dtos::HallDto dto;
            dto.capacity = body["capacity"].i();
            dto.type = body["type"].i();

            auto hall = dtos::FromDto(dto);

            bool ok = service::LocationService::AddHall(locationId, hall);

            if (!ok)
                return crow::response(400, "Cannot add hall");

            return crow::response(201, "hall added");
        });

        // REMOVE HALL
        CROW_ROUTE(app, "/locations/<int>/halls/<int>")
        .methods(crow::HTTPMethod::DELETE)
        ([](int locationId, int hallId)
        {
            bool ok = service::LocationService::RemoveHall(locationId, hallId);

            if (!ok)
                return crow::response(400, "Cannot remove hall");

            return crow::response(200, "hall removed");
        });

        //UPDATE HALL
        CROW_ROUTE(app, "/locations/<int>/halls/<int>")
        .methods(crow::HTTPMethod::PUT)
        ([](const crow::request& req, int locationId, int hallId)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400, "Invalid JSON");

            if (!body.has("capacity"))
                return crow::response(400, "Missing capacity");

            int capacity = body["capacity"].i();

            bool ok = service::LocationService::UpdateHall(
                locationId,
                hallId,
                capacity
            );

            if (!ok)
                return crow::response(400, "Cannot update hall");

            return crow::response(200, "hall updated");
        });

        //READ ALL HALLS
        CROW_ROUTE(app, "/locations/<int>/halls")
        ([](int locationId)
        {
            auto opt = LocationController::locations.GetById(locationId);

            if (!opt)
                return crow::response(404, "Location not found");

            auto location = opt.value();

            auto halls = location.GetHalls(); // vector<Hall>

            crow::json::wvalue res;

            for (size_t i = 0; i < halls.size(); i++)
            {
                res[i]["id"] = halls[i].id;
                res[i]["capacity"] = halls[i].capacity;
                res[i]["type"] = static_cast<int>(halls[i].type);
            }

            return crow::response(res);
        });

        //READ ONE HALL
        CROW_ROUTE(app, "/locations/<int>/halls/<int>")
        ([](int locationId, int hallId)
        {
            auto opt = LocationController::locations.GetById(locationId);

            if (!opt)
                return crow::response(404, "Location not found");

            auto location = opt.value();

            const domain::Hall* hall = location.GetHallById(hallId);

            if (!hall)
                return crow::response(404, "Hall not found");

            crow::json::wvalue res;
            res["id"] = hall->id;
            res["capacity"] = hall->capacity;
            res["type"] = static_cast<int>(hall->type);

            return crow::response(res);
        });

        // =========================================================
        // SCHEDULE
        // =========================================================

        // ADD SCHEDULE
        CROW_ROUTE(app, "/locations/<int>/schedule")
        .methods(crow::HTTPMethod::POST)
        ([](const crow::request &req, int locationId)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400);

            dtos::ScheduleDto dto;

            dto.groupId = body["groupId"].i();
            dto.hallId = body["hallId"].i();
            dto.day = body["day"].i();
            dto.time = body["time"].i();
            dto.isOccupied = body["isOccupied"].b();

            auto schedule = dtos::FromDto(dto);

            bool ok = service::LocationService::AddSchedule(locationId, schedule);

            if (!ok)
                return crow::response(400, "Cannot add schedule");

            return crow::response(201, "schedule added");
        });

        // REMOVE SCHEDULE
        CROW_ROUTE(app, "/locations/<int>/schedule")
        .methods(crow::HTTPMethod::DELETE)
        ([](const crow::request &req, int locationId)
        {
            auto body = crow::json::load(req.body);

            if (!body)
                return crow::response(400);

            dtos::ScheduleDto dto;

            dto.groupId = body["groupId"].i();
            dto.hallId = body["hallId"].i();
            dto.day = body["day"].i();
            dto.time = body["time"].i();

            auto schedule = dtos::FromDto(dto);

            bool ok = service::LocationService::RemoveSchedule(locationId, schedule);

            if (!ok)
                return crow::response(400, "Cannot remove schedule");

            return crow::response(200, "schedule removed");
        });

        //READ ALL SCHEDULE
        CROW_ROUTE(app, "/locations/<int>/schedule")
        ([](int locationId)
        {
            auto opt = LocationController::locations.GetById(locationId);

            if (!opt)
                return crow::response(404);

            const auto& location = opt.value();

            auto schedule = location.GetScheduleList();

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

        //SCHEDULE BY HALL
        CROW_ROUTE(app, "/locations/<int>/halls/<int>/schedule")
        ([](int locationId, int hallId)
        {
            auto schedule = service::LocationService::GetScheduleByHall(locationId, hallId);

            crow::json::wvalue res;

            for (size_t i = 0; i < schedule.size(); i++)
            {
                res[i]["groupId"] = schedule[i].groupId;
                res[i]["day"] = static_cast<int>(schedule[i].day);
                res[i]["time"] = static_cast<int>(schedule[i].time);
                res[i]["hallId"] = schedule[i].hallId;
            }

            return crow::response(res);
        });

        //SCHEDULE BY DAY
        CROW_ROUTE(app, "/locations/<int>/schedule")
        ([](const crow::request& req, int locationId)
        {
            auto dayParam = req.url_params.get("day");

            if (!dayParam)
                return crow::response(400, "Missing day");

            int dayInt = std::stoi(dayParam);

            auto schedule = service::LocationService::GetScheduleByDay(
                locationId,
                static_cast<domain::Day>(dayInt)
            );

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