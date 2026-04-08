#pragma once
#include <vector>
#include "elan/domain/Client.h"

namespace storage
{
    class ClientStorage
    {
    public:
        void AddClient(const domain::Client &client);
        std::vector<domain::Client> GetAllClients();
        void UpdateClient(const domain::Client);
        void DeleteClient(int Id);
    };
}
