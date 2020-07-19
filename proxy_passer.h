/***********************
 * @file: proxy_passer.h
 * @author: shizuku
 * @date: 2020/7/18
 ***********************/
#ifndef SERVER_PROXY_PASSER_H
#define SERVER_PROXY_PASSER_H

#include <string>
#include <map>

#include "server_router.h"
#include "http/request.h"
#include "http/response.h"

class proxy_passer {
public:
    const int BUFFER_SIZE = 4096;

    explicit proxy_passer(std::map<std::string, std::map<std::string, std::string>, cmp> &&map);

    bool pass(const http::request &req, const http::response &res);

private:
    std::map<std::string, std::map<std::string, std::string>, cmp> map;
};

#endif //SERVER_PROXY_PASSER_H
