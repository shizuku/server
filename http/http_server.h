/***********************
 * @file: http_server.h
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/
#ifndef HTTP_HTTP_SERVER_H
#define HTTP_HTTP_SERVER_H

#include <iostream>
#include <thread>

#include <sys/socket.h>
#include <netinet/in.h>
#include <libnet.h>

#include "http_request.h"
#include "http_response.h"

namespace http {
    using http_server_callback_type = void (*)(const http_request &, http_response);

    const int BUFFER_SIZE = 4096;

    class http_server {
    public:
        explicit http_server(http_server_callback_type callback, std::ostream &log = std::cout);

        http_server &listen(int port);

    private:
        static void connect(int client_socket, http_server_callback_type callback);

        http_server_callback_type callback;
        std::ostream &log;
    };

    http_server create_server(http_server_callback_type callback);
};

#endif //HTTP_HTTP_SERVER_H
