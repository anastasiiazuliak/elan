#pragma once
#include <vector>
#include <optional>
#include "elan/domain/User.h"

namespace storage
{
    class UserStorage
    {
    public:
        void Add(const domain::User &user);
        std::optional<domain::User> GetById(int id);
        std::vector<domain::User> GetAll();
        void Update(const domain::User &user);
        void Delete(int Id);
    };
}
