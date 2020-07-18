/***********************
 * @file: server_router.cpp
 * @author: shizuku
 * @date: 2020/7/17
 ***********************/
#include "server_router.h"


server_router::server_router(std::map<std::string, std::string, cmp> &&map) : map((map)) {
    for (auto &i:this->map) {
        i.second.append("/");
    }
    try {
        root = map.at("/");
    } catch (const std::out_of_range &e) {
        throw std::out_of_range("root dir not set");
    }
}

std::string server_router::route(const std::string &request_path) {
    std::string p{};
    for (auto &i:map) {
        if (request_path.compare(0, i.first.length(), i.first) == 0) {
            auto x = request_path;
            return dir(x.replace(0, i.first.length(), i.second));
        }
    }
    p = root + request_path;
    return dir(p);
}

std::string server_router::dir(const std::string &p) {
    struct stat buf;
    ::stat(p.c_str(), &buf);
    if (S_ISDIR(buf.st_mode)) {
        for (auto &i:index_extensions) {
            auto path = p + "/index." + i;
            if (access(path.c_str(), 0) != -1) {
                return path;
            }
        }
        throw error_file_not_found();
    } else {
        return p;
    }
}
