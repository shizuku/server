/***********************
 * @file: server_router.h
 * @author: shizuku
 * @date: 2020/7/17
 ***********************/
#ifndef SERVER_SERVER_ROUTER_H
#define SERVER_SERVER_ROUTER_H

#include <map>
#include <string>
#include <iostream>
#include <vector>

#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include "http/error.h"

struct cmp_ {
    bool operator()(const std::string &k1, const std::string &k2) const {
        int l1 = 0;
        int l2 = 0;
        int pos = 0;
        while ((pos = k1.find('/', pos)) != std::string::npos) {
            ++pos;
            ++l1;
        }
        pos = 0;
        while ((pos = k2.find('/', pos)) != std::string::npos) {
            ++pos;
            ++l2;
        }
        if (l1 == l2) {
            return k1.length() > k2.length();
        } else {
            return l1 > l2;
        }
    }
};

using cmp = cmp_;

class server_router {
public:
    explicit server_router(std::map<std::string, std::string, cmp> &&map);

    std::string route(const std::string &request_path);

private:
    std::string dir(const std::string &p);

    std::string root;
    std::map<std::string, std::string, cmp> map;
    const std::vector<std::string> index_extensions{"html", "htm", "jsp", "php"};
};

#endif //SERVER_SERVER_ROUTER_H
