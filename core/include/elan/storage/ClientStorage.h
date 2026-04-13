#pragma once
#include <vector>
#include <optional>
#include "elan/domain/Client.h"

namespace storage
{
    class ClientStorage
    {
    public:
        void Add(const domain::Client &client);
        std::optional<domain::Client> GetById(int id);
        std::vector<domain::Client> GetAll();
        void Update(const domain::Client &client);
        void Delete(int Id);
    };
}
