/***********************
 * @file: main.cpp
 * @author: shizuku
 * @date: 2020/7/15
 ***********************/
#include <iostream>

#include "server_config.h"
#include "http/http_server.h"

void root(const http::http_request &req, http::http_response res) {
    std::cout << req.method << req.url << std::endl;

    std::time(nullptr);
    res.write_head(200, "OK", http::http_response_headers{std::map<std::string, std::string>{
            {"Date",         "Sat, 31 Dec 2005 23:59:59 GMT"},
            {"Content-Type", "text/html; charset=utf-8"},
    }});

    res.write("<html>\n"
              "<head>\n"
              "<title>Wrox Homepage</title>\n"
              "</head>\n"
              "<body>\n"
              "hahaahahahahahaah\n"
              "</body>\n"
              "</html>");
    res.end();
}

int main() {
    const std::string config_filename = "config.json";

    const server_config sc(config_filename);

    http::create_server(&root).listen(sc.port);

    return 0;
}
