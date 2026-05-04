#include "elan/services/GroupService.h"

storage::Storage<domain::Group> groups(
        "../data/groups.bin",
        "../data/groups.bin"
    );

namespace service
{
    std::vector<domain::Group> GroupService::GetGroupsByCoachId(int id)
    {
        std::vector<domain::Group> allGroups = groups.GetAll();
        std::vector<domain::Group> coachGroups;

        for(auto g : allGroups)
        {
            if (g.GetCoachId() == id)
            {
                coachGroups.push_back(g);
            }
        }

        return coachGroups;
    };
}