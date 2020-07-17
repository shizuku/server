/***********************
 * @file: server_router.h
 * @author: shizuku
 * @date: 2020/7/17
 ***********************/
#ifndef SERVER_SERVER_ROUTER_H
#define SERVER_SERVER_ROUTER_H

#include <map>
#include <string>

class server_router {
public:
    explicit server_router(std::map<std::string, std::string> &&map);

    std::map<std::string, std::string> map;

    std::string route(const std::string &request_path);
};

#endif //SERVER_SERVER_ROUTER_H
