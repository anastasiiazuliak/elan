#include "elan/services/LocationService.h"

namespace service
{
    storage::Storage<domain::Location> LocationService::locations(
        "../data/locations.bin",
        "../data/locations_id.bin");

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

        return locations.Update(loc);
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

        return locations.Update(loc);
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

        return locations.Update(loc);
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

        return locations.Update(loc);
    }
}