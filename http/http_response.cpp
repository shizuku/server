/***********************
 * @file: http_response.cpp
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/

#include "http_response.h"

http::http_response::http_response(int client_socket) : client_socket(client_socket), head{}, body{} {

}

void http::http_response::end() {
    head << "HTTP/1.0 200 OK \r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 137582\r\n"
            "Expires: Thu, 05 Dec 1997 16:00:00 GMT\r\n"
            "Last-Modified: Wed, 5 August 1996 15:55:28 GMT\r\n"
            "Server: Apache 0.84\r\n";

    auto str = head.str() + "\r\n" + body.str();
    ::send(client_socket, str.c_str(), str.length(), 0);
    ::close(client_socket);
}
