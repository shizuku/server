/***********************
 * @file: request.h
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/
#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <map>
#include <string>
#include <vector>
#include <sstream>

namespace http {
    class request_header {
    public:
        request_header();

        explicit request_header(const std::string &head);

        void pass(const std::string &url_, const std::string &host, int port);

        std::vector<std::string> raw;
        std::map<std::string, std::string> map;
    };

    class request {
    public:
        explicit request(const std::string &raw_headers);

        void pass(const std::string &url_, const std::string &host, int port);

        std::string str();

        std::string method;
        std::string url;
        std::string http_version;
        int http_version_major;
        int http_version_minor;
        std::string body;

        std::string raw;
        request_header headers;
    };
}

#endif //HTTP_REQUEST_H
