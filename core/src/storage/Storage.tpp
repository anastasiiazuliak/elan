#include "elan/storage/Storage.h"
#include "elan/storage/ID.h"

#include <fstream>
#include <optional>
#include <algorithm>
#include <vector>

namespace storage
{
    template <typename T>
    Storage<T>::Storage(const char *file, const char *id) : file_Name(file), id_File(id) {};

    template <typename T>
    void Storage<T>::Add(T &entity)
    {
        id::ID gen(id_File);

        entity.SetId(gen.Get());

        std::ofstream file(file_Name, std::ios::binary | std::ios::app);

        if (!file.is_open())
            return;

        file.write(reinterpret_cast<char *>(&entity), sizeof(T));
    }

    template <typename T>
    std::optional<T> Storage<T>::GetById(int id)
    {
        std::ifstream file(file_Name, std::ios::binary);

        T obj;

        while (file.read(reinterpret_cast<char *>(&obj), sizeof(T)))
        {
            if (obj.GetId() == id)
                return obj;
        }

        return std::nullopt;
    }

    template <typename T>
    std::vector<T> Storage<T>::GetAll()
    {
        std::vector<T> result;

        std::ifstream file(file_Name, std::ios::binary);

        T obj;

        while (file.read(reinterpret_cast<char *>(&obj), sizeof(T)))
        {
            result.push_back(obj);
        }

        return result;
    }

    template <typename T>
    bool Storage<T>::Update(const T &updated)
    {
        auto all = GetAll();

        bool found = false;

        for (auto &x : all)
        {
            if (x.GetId() == updated.GetId())
            {
                x = updated;
                found = true;
                break;
            }
        }

        if (!found)
            return false;

        std::ofstream file(file_Name, std::ios::binary | std::ios::trunc);

        for (auto &x : all)
            file.write(reinterpret_cast<char *>(&x), sizeof(T));

        return true;
    }

    template <typename T>
    bool Storage<T>::Delete(int id)
    {
        auto all = GetAll();

        auto old = all.size();

        all.erase(std::remove_if(all.begin(), all.end(), [id](auto &x)
                                 { return x.GetId() == id; }),
                  all.end());

        if (old == all.size())
            return false;

        std::ofstream file(file_Name, std::ios::binary | std::ios::trunc);

        for (auto &x : all)
            file.write(reinterpret_cast<const char *>(&x), sizeof(T));

        return true;
    }
}