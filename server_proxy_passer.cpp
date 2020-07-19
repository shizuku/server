/***********************
 * @file: server_proxy_passer.cpp
 * @author: shizuku
 * @date: 2020/7/18
 ***********************/
#include "server_proxy_passer.h"

server_proxy_passer::server_proxy_passer(std::map<std::string, std::map<std::string, std::string>, cmp> &&map) : map{map} {

}

bool server_proxy_passer::pass(const http::request &req, const http::response &res) {
    std::string p{};
    for (auto &i:map) {
        if (req.url.compare(0, i.first.length(), i.first) == 0) {
            auto host = i.second["host"];
            auto port = atoi(i.second["port"].c_str());
            auto url = i.second["url"];
            //std::cout << "proxy to :" << host << ":" << port << url << std::endl;
            auto r = req;
            r.pass(url, host, port);
            int sock = socket(AF_INET, SOCK_STREAM, 0);
            sockaddr_in server_addr{};
            server_addr.sin_family = AF_INET;
            server_addr.sin_addr.s_addr = inet_addr(host.c_str());
            server_addr.sin_port = htons(port);
            connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));

            auto s = r.str();
            send(sock, s.c_str(), s.length(), 0);

            char buffer[BUFFER_SIZE];
            int nCount;
            while ((nCount = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
                res.write(buffer, nCount);
            }
            res.shutdown();
            return true;
        }
    }
    return false;
}
