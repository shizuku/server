/***********************
 * @file: response.h
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/
#ifndef HTTP_HTTP_RESPONSE_H
#define HTTP_HTTP_RESPONSE_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include <sys/socket.h>
#include <netinet/in.h>
#include <libnet.h>

namespace http {
    class response_headers {
    public:
        explicit response_headers(std::map<std::string, std::string> m);

        std::map<std::string, std::string> map;
    };

    class response {
    public:
        explicit response(int client_socket);

        void write(const std::string &trunk) const;

        void write(const char *s, size_t len) const;

        void write_head(int status_code, 
                        const std::string &reason_phrase, 
                        const response_headers &headers) const;

        void end() const;

        void shutdown() const;

    private:
        int client_socket;
    };
}

#endif //HTTP_HTTP_RESPONSE_H
