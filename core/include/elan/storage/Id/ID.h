#pragma once

#include <string>

namespace id
{
    class ID
    {
        std::string file_name;

        int Read();
        void Write(int id);

    public:
        ID(const std::string &file_name);
        int Get();
    };
}