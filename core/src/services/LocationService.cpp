#include "elan/services/LocationService.h"
#include "elan/storage/Storage.h"

storage::Storage<domain::Location> locations(
    "../data/location.bin",
    "../data/location_id.bin");

namespace service
{
    bool LocationService::AddHall(int locationId, domain::Hall& hall)
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

        bool LocationService::AddSchedule(int locationId, domain::Schedule s)
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

    bool LocationService::RemoveSchedule(int locationId, domain::Schedule s)
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