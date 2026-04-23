#pragma once
#include <vector>
#include <optional>
#include "elan/domain/User.h"

namespace storage
{
    class UserStorage
    {
    public:
        void Add(domain::User &user);
        std::optional<domain::User> GetById(int id);
        std::vector<domain::User> GetAll();
        bool Update(const domain::User &user);
        bool Delete(int id);
    };
}
