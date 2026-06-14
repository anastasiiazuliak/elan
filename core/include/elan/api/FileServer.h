#pragma once
#include <crow.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

inline bool endsWith(const std::string& str, const std::string& suffix)
{
    if (str.size() < suffix.size()) return false;
    return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

inline crow::response serveFile(const std::string& path)
{
    namespace fs = std::filesystem;

    fs::path filePath(path);
    if (!fs::exists(filePath))
    {
        const std::string prefix = "../frontend/";
        if (path.rfind(prefix, 0) == 0)
        {
            filePath = fs::path("frontend") / path.substr(prefix.size());
        }
    }

    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open())
        return crow::response(404, "Not found");

    std::stringstream ss;
    ss << file.rdbuf();

    crow::response res(ss.str());

    const std::string resolvedPath = filePath.string();

    if (endsWith(resolvedPath, ".html"))
        res.add_header("Content-Type", "text/html; charset=utf-8");

    else if (endsWith(resolvedPath, ".css"))
        res.add_header("Content-Type", "text/css; charset=utf-8");

    else if (endsWith(resolvedPath, ".js"))
        res.add_header("Content-Type", "application/javascript; charset=utf-8");

    return res;
}
