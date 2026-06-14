#include "elan/api/MembershipController.h"
#include "elan/services/MembershipService.h"
#include "elan/storage/Storages.h"

namespace api
{
    void MembershipController::RegisterRoutes(crow::SimpleApp &app)
    {
        // CREATE
        CROW_ROUTE(app, "/memberships")
        .methods(crow::HTTPMethod::POST)
        ([](const crow::request &req)
        {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400);

            bool ok = service::MembershipService::CreateMembership(
                body["clientId"].i(),
                body["groupId"].i(),
                body["subscriptionId"].i()
            );

            return crow::response(ok ? 201 : 400);
        });

        // GET BY CLIENT (ACTIVE + FULL INFO)
        CROW_ROUTE(app, "/clients/<int>/memberships")
        ([](int clientId)
        {
            auto list = service::MembershipService::GetActiveByClient(clientId);

            crow::json::wvalue res;

            for (size_t i = 0; i < list.size(); i++)
            {
                auto m = list[i];

                auto clientOpt = storages::Clients().GetById(m.GetClientId());
                auto groupOpt  = storages::Groups().GetById(m.GetGroupId());

                if (!clientOpt || !groupOpt)
                    continue;

                auto client = clientOpt.value();
                auto group  = groupOpt.value();

                res[i]["id"] = m.GetId();

                res[i]["clientId"] = client.GetId();
                res[i]["clientFirstName"] = client.GetFirstName();
                res[i]["clientLastName"] = client.GetLastName();

                res[i]["groupId"] = group.GetId();
                res[i]["groupName"] = group.GetName();

                res[i]["subscriptionId"] = m.GetSubscriptionId();

                res[i]["startDate"] = common::FormatDate(m.GetStartDate());
                res[i]["endDate"] = common::FormatDate(m.GetEndDate());

                res[i]["remainingWorkouts"] = m.GetRemainingWorkouts();
                res[i]["completedWorkouts"] = m.GetCompletedWorkouts();
            }

            return crow::response(res);
        });

        // GET BY GROUP (ACTIVE)
        CROW_ROUTE(app, "/groups/<int>/memberships")
        ([](int groupId)
        {
            auto list = service::MembershipService::GetActiveByGroup(groupId);

            crow::json::wvalue res;

            for (size_t i = 0; i < list.size(); i++)
            {
                auto m = list[i];

                auto clientOpt = storages::Clients().GetById(m.GetClientId());
                auto groupOpt  = storages::Groups().GetById(m.GetGroupId());

                if (!clientOpt || !groupOpt)
                    continue;

                auto client = clientOpt.value();
                auto group  = groupOpt.value();

                res[i]["id"] = m.GetId();

                res[i]["clientId"] = client.GetId();
                res[i]["clientFirstName"] = client.GetFirstName();
                res[i]["clientLastName"] = client.GetLastName();

                res[i]["groupId"] = group.GetId();
                res[i]["groupName"] = group.GetName();
                res[i]["subscriptionId"] = m.GetSubscriptionId();

                res[i]["startDate"] = common::FormatDate(m.GetStartDate());
                res[i]["endDate"] = common::FormatDate(m.GetEndDate());

                res[i]["remainingWorkouts"] = m.GetRemainingWorkouts();
                res[i]["completedWorkouts"] = m.GetCompletedWorkouts();
            }

            return crow::response(res);
        });

        // USE WORKOUT
        CROW_ROUTE(app, "/memberships/<int>/use")
        .methods(crow::HTTPMethod::PATCH)
        ([](int id)
        {
            bool ok = service::MembershipService::UseWorkout(id);
            return crow::response(ok ? 200 : 400);
        });
    }
}
