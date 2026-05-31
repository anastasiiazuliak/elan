#include "elan/services/LocationService.h"

namespace service
{
    storage::Storage<domain::Location> LocationService::locations(
        constants::LOCATIONS_FILE,
        constants::LOCATIONS_ID_FILE);

    bool LocationService::AddHall(int locationId, domain::Hall &hall)
    {
        auto locOpt = locations.GetById(locationId);
        if (!locOpt.has_value())
        {
            return false;
        }

        auto loc = locOpt.value();

        if (!loc.AddHall(hall))
        {
            return false;
        }

        return locations.Update(locationId, loc);
    }

    bool LocationService::RemoveHall(int locationId, int hallId)
    {
        auto locOpt = locations.GetById(locationId);
        if (!locOpt.has_value())
        {
            return false;
        }

        auto loc = locOpt.value();

        if (!loc.RemoveHall(hallId))
        {
            return false;
        }

        return locations.Update(locationId, loc);
    }

    bool LocationService::UpdateHall(int locationId, int hallId, int capacity)
    {
        auto locOpt = locations.GetById(locationId);

        if (!locOpt)
            return false;

        auto loc = locOpt.value();

        if (!loc.UpdateHall(hallId, capacity))
            return false;

        return locations.Update(locationId, loc);
    }

    bool LocationService::AddSchedule(int locationId, const domain::Schedule &s)
    {
        auto locOpt = locations.GetById(locationId);
        if (!locOpt.has_value())
        {
            return false;
        }

        auto loc = locOpt.value();

        if (!loc.AddSchedule(s))
        {
            return false;
        }

        return locations.Update(locationId, loc);
    }

    bool LocationService::RemoveSchedule(int locationId, const domain::Schedule &s)
    {
        auto locOpt = locations.GetById(locationId);
        if (!locOpt.has_value())
        {
            return false;
        }

        auto loc = locOpt.value();

        if (!loc.RemoveSchedule(s))
        {
            return false;
        }

        return locations.Update(locationId, loc);
    }

    std::vector<domain::Schedule> LocationService::GetScheduleByHall(int locationId, int hallId)
    {
        std::vector<domain::Schedule> result;

        auto locOpt = locations.GetById(locationId);

        if (!locOpt)
            return result;

        const auto& loc = locOpt.value();

        auto all = loc.GetScheduleList();

        for (const auto& s : all)
        {
            if (s.hallId == hallId)
                result.push_back(s);
        }

        return result;
    }

    std::vector<domain::Schedule> LocationService::GetScheduleByDay(int locationId, domain::Day day)
    {
        std::vector<domain::Schedule> result;

        auto locOpt = locations.GetById(locationId);

        if (!locOpt)
            return result;

        const auto& loc = locOpt.value();

        auto all = loc.GetScheduleList();

        for (const auto& s : all)
        {
            if (s.day == day)
                result.push_back(s);
        }

        return result;
    }

    std::vector<domain::Schedule> LocationService::GetScheduleByGroup(int locationId, int groupId)
    {
        std::vector<domain::Schedule> result;

        auto locOpt = locations.GetById(locationId);

        if (!locOpt)
            return result;

        const auto& loc = locOpt.value();

        auto all = loc.GetScheduleList();

        for (const auto& s : all)
        {
            if (s.groupId == groupId)
                result.push_back(s);
        }

        return result;
    }
}