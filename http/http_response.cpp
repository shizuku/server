/***********************
 * @file: http_response.cpp
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/

#include "http_response.h"

#include <utility>

http::http_response::http_response(int client_socket) : client_socket(client_socket) {}

void http::http_response::write_head(int status_code, const std::string &reason_phrase,
                                     const http::http_response_headers &headers) const {
    std::stringstream head;
    head << "HTTP/1.1 " << status_code << " " << reason_phrase << "\r\n";
    for (auto &i:headers.map) {
        head << i.first << ": " << i.second << "\r\n";
    }
    head << "\r\n";
    auto s = head.str();
    ::send(client_socket, s.c_str(), s.length(), 0);
}

void http::http_response::write(const std::string &trunk) const {
    ::send(client_socket, trunk.c_str(), trunk.length(), 0);
}

void http::http_response::end() const {
    ::close(client_socket);
}


http::http_response_headers::http_response_headers(std::map<std::string, std::string> m) : map(std::move(m)) {

}
