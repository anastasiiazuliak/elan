#pragma once
#include <optional>
#include <vector>

namespace storage
{
    template <typename T>
    class Storage
    {
        const char *file_Name;
        const char *id_File;

    public:
        Storage(const char *file_Name, const char *id_File);
        void Add(T &entity);
        std::optional<T> GetById(int id);
        std::vector<T> GetAll();
        bool Update(const T &updated);
        bool Delete(int id);
    };

}

#include "../../../src/storage/Storage.tpp"
