/***********************
 * @file: server.h
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

#include "request.h"
#include "response.h"

namespace http {
    using server_callback_type = void (*)(const request &, response);

    const int BUFFER_SIZE = 4096;

    class server {
    public:
        explicit server(server_callback_type callback, std::ostream &log = std::cout);

        server &listen(int port);

    private:
        static void connect(int client_socket, server_callback_type callback);

        server_callback_type callback;
        std::ostream &log;
    };

    server create_server(server_callback_type callback);
};

#endif //HTTP_HTTP_SERVER_H
