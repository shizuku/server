/***********************
 * @file: http_server.cpp
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/
#include "http_server.h"


http::http_server &http::http_server::listen(int port) {
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in server_addr{};
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));

    ::listen(server_socket, 20);
    log << "listening port: " << port << "\n";
    while (1) {
        struct sockaddr_in client_addr{};
        socklen_t client_addr_size = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_addr_size);

        std::thread connection{connect, client_socket, callback};
        connection.detach();
    }

    close(server_socket);

    return *this;
}

http::http_server::http_server(http_server_callback_type callback, std::ostream &log) : callback(callback), log(log) {}


void http::http_server::connect(int client_socket, http_server_callback_type callback) {
    std::string req{};
    char buffer[BUFFER_SIZE] = {0};
    int len;
    while (true) {
        len = recv(client_socket, buffer, BUFFER_SIZE, 0);
        req.append(buffer);
        if (len < BUFFER_SIZE)break;
    }
    if (req.empty()) {
        return;
    }
    callback(http_request{req}, http_response{client_socket});
}

http::http_server http::create_server(http_server_callback_type callback) {
    http_server server{callback};
    return server;
}
