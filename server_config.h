/***********************
 * @file: server_config.h
 * @author: shizuku
 * @date: 2020/7/15
 ***********************/
#ifndef SERVER_SERVER_CONFIG_H
#define SERVER_SERVER_CONFIG_H

#include <string>
#include <map>
#include <iostream>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

class server_config {
public:
    server_config() = delete;

    explicit server_config(const std::string &filename);

    int port;
    std::string server;
    std::map<std::string, std::string> router;
};

std::ostream &operator<<(std::ostream &o, const server_config &sc);

#endif //SERVER_SERVER_CONFIG_H
