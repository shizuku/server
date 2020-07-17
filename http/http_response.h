/***********************
 * @file: http_response.h
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/
#ifndef HTTP_HTTP_RESPONSE_H
#define HTTP_HTTP_RESPONSE_H

#include <iostream>
#include <sstream>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <libnet.h>

namespace http {
    class http_response {
    public:
        explicit http_response(int client_socket);

        std::stringstream head;
        std::stringstream body;

        void end();

    private:
        int client_socket;
    };
}

#endif //HTTP_HTTP_RESPONSE_H
