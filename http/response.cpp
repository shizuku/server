/***********************
 * @file: response.cpp
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/

#include "response.h"

#include <utility>

http::response::response(int client_socket) : client_socket(client_socket) {}

void http::response::write_head(int status_code, const std::string &reason_phrase,
                                const http::response_headers &headers) const {
    std::stringstream head;
    head << "HTTP/1.1 " << status_code << " " << reason_phrase << "\r\n";
    for (auto &i:headers.map) {
        head << i.first << ": " << i.second << "\r\n";
    }
    head << "\r\n";
    auto s = head.str();
    ::send(client_socket, s.c_str(), s.length(), 0);
}

void http::response::write(const std::string &trunk) const {
    ::send(client_socket, trunk.c_str(), trunk.length(), 0);
}

void http::response::end() const {
    ::close(client_socket);
}

void http::response::shutdown() const {
    ::shutdown(client_socket, SHUT_WR);
}

void http::response::write(const char *s, size_t len) const {
    ::send(client_socket, s, len, 0);
}

http::response_headers::response_headers(std::map<std::string, std::string> m) : map(std::move(m)) {

}
