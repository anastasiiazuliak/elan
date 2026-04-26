#include "elan/storage/ID.h"

#include <iostream>
#include <fstream>
#include <cstring>

static constexpr int INVALID_ID = -1;

namespace id
{
    ID::ID(const std::string &file_name) : file_name(file_name) {}

    int ID::Read()
    {
        std::ifstream file(file_name, std::ios::binary);
        if (!file)
            return INVALID_ID;

        int id = INVALID_ID;
        if (!file.read(reinterpret_cast<char *>(&id), sizeof(int)))
            return INVALID_ID;

        return id;
    }

    void ID::Write(int id)
    {
        std::ofstream file(file_name, std::ios::binary | std::ios::trunc);
        if (file.is_open())
            file.write(reinterpret_cast<char *>(&id), sizeof(int));
    }

    int ID::Get()
    {
        int id = Read();
        if (id < 0)
            id = 0;
        ++id;
        Write(id);

        return id;
    }
}