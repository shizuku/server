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
}

std::ostream &operator<<(std::ostream &o, const server_config &sc) {
    o << "port: " << sc.port << "\n";
    o << "router:\n";
    for (auto &i:sc.router) {
        o << "\t" << i.first << "\t\t" << i.second << "\n";
    }
    return o;
}
