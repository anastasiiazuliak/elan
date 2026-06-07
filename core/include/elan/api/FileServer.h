#pragma once
#include <crow.h>
#include <fstream>
#include <sstream>

inline bool endsWith(const std::string& str, const std::string& suffix)
{
    if (str.size() < suffix.size()) return false;
    return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

inline crow::response serveFile(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
        return crow::response(404, "Not found");

    std::stringstream ss;
    ss << file.rdbuf();

    crow::response res(ss.str());

    if (endsWith(path, ".html"))
        res.add_header("Content-Type", "text/html");

    else if (endsWith(path, ".css"))
        res.add_header("Content-Type", "text/css");

    else if (endsWith(path, ".js"))
        res.add_header("Content-Type", "application/javascript");

    return res;
}