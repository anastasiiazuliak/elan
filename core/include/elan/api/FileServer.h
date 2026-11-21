#pragma once
#include <crow.h>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>

inline std::optional<std::string> decodeUrlPath(const std::string& value)
{
    std::string decoded;
    decoded.reserve(value.size());

    for (std::size_t i = 0; i < value.size(); ++i)
    {
        if (value[i] == '%')
        {
            if (i + 2 >= value.size())
                return std::nullopt;

            unsigned int byte = 0;
            const char* end = value.data() + i + 3;
            const auto result = std::from_chars(value.data() + i + 1, end, byte, 16);
            if (result.ec != std::errc{} || result.ptr != end || byte == 0)
                return std::nullopt;

            decoded.push_back(static_cast<char>(byte));
            i += 2;
        }
        else
        {
            decoded.push_back(value[i]);
        }
    }

    return decoded;
}

inline crow::response serveFile(const std::string& path)
{
    namespace fs = std::filesystem;

    const auto decodedPath = decodeUrlPath(path);
    if (!decodedPath || decodedPath->find_first_of("\\:") != std::string::npos)
        return crow::response(404, "Not found");

    const auto relativePath = fs::u8path(*decodedPath);
    if (relativePath.has_root_path())
        return crow::response(404, "Not found");

    static const auto frontendRoot = fs::canonical("frontend");
    std::error_code error;
    const auto filePath = fs::weakly_canonical(frontendRoot / relativePath, error);
    const auto resolvedRelativePath = filePath.lexically_relative(frontendRoot);
    if (error || resolvedRelativePath.empty() || *resolvedRelativePath.begin() == ".." ||
        !fs::is_regular_file(filePath, error))
        return crow::response(404, "Not found");

    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open())
        return crow::response(404, "Not found");

    std::stringstream ss;
    ss << file.rdbuf();

    crow::response res(ss.str());

    const auto extension = filePath.extension().u8string();

    if (extension == ".html")
        res.add_header("Content-Type", "text/html; charset=utf-8");

    else if (extension == ".css")
        res.add_header("Content-Type", "text/css; charset=utf-8");

    else if (extension == ".js")
        res.add_header("Content-Type", "application/javascript; charset=utf-8");

    else if (extension == ".png")
        res.add_header("Content-Type", "image/png");

    else if (extension == ".jpg" || extension == ".jpeg")
        res.add_header("Content-Type", "image/jpeg");

    return res;
}
