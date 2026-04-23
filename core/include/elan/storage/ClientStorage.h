#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Client.h"

namespace storage
{
    class ClientStorage
    {
    public:
        void Add(domain::Client &client);
        std::optional<domain::Client> GetById(int id);
        std::vector<domain::Client> GetAll();
        bool Update(const domain::Client &client);
        bool Delete(int id);
    };
}
