/***********************
 * @file: server_config.cpp
 * @author: shizuku
 * @date: 2020/7/15
 ***********************/
#include "server_config.h"

server_config::server_config(const std::string &filename) {
    boost::property_tree::ptree root;
    boost::property_tree::read_json(filename, root);

    port = root.get<int>("port");

    auto r = root.get_child("router");
    for (auto &i : r) {
        router.insert_or_assign(i.first, i.second.get<std::string>(""));
    }

    auto e = root.get_child("expires");
    for (auto &i : e) {
        expires.insert_or_assign(i.first, i.second.get<std::string>(""));
    }

    auto ep = root.get_child("error_pages");
    for (auto &i : ep) {
        error_pages.insert_or_assign(i.first, i.second.get<std::string>(""));
    }

    auto pp = root.get_child("proxy_pass");
    for (auto &i : pp) {
        proxy_pass.insert_or_assign(i.first, std::map<std::string, std::string>{
                {"host", i.second.get<std::string>("host")},
                {"port", i.second.get<std::string>("port")},
                {"url",  i.second.get<std::string>("url")},
        });
    }
}

std::ostream &operator<<(std::ostream &o, const server_config &sc) {
    o << "port: " << sc.port << "\n";
    o << "router:\n";
    for (auto &i:sc.router) {
        o << "\t" << i.first << "\t\t" << i.second << "\n";
    }
    return o;
}
