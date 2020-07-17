/***********************
 * @file: main.cpp
 * @author: shizuku
 * @date: 2020/7/15
 ***********************/
#include <iostream>

#include "server_config.h"
#include "http/http_server.h"

void root(const http::http_request &req, http::http_response res) {
    std::cout << "request: " << req.url << std::endl;
    std::cout << req.method << req.url << std::endl;
    for (auto &i:req.headers.map) {
        std::cout << i.first << " : " << i.second << std::endl;
    }
    std::cout << std::endl << std::endl;
    res.body << "<html>\n"
                "  <body>Hello World</body>\n"
                "</html>";
    res.end();
}

int main() {
    const std::string config_filename = "config.json";

    const server_config sc(config_filename);

    http::create_server(&root).listen(sc.port);

    return 0;
}
