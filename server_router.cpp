/***********************
 * @file: server_router.cpp
 * @author: shizuku
 * @date: 2020/7/17
 ***********************/
#include "server_router.h"

#include <utility>

server_router::server_router(std::map<std::string, std::string> &&map) : map(std::move(map)) {

}

std::string server_router::route(const std::string &request_path) {
    for (auto &i:map) {

    }
    return "/home/shizuku/workspace/Webstorm/untitled/build" + request_path;
}
