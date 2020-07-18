/***********************
 * @file: http_request.h
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/
#ifndef HTTP_HTTP_REQUEST_H
#define HTTP_HTTP_REQUEST_H

#include <map>
#include <string>
#include <vector>

namespace http {
    class http_request_header {
    public:
        http_request_header();

        explicit http_request_header(const std::string &head);

        std::vector<std::string> raw;
        std::map<std::string, std::string> map;
    };

    class http_request {
    public:
        explicit http_request(const std::string &raw_headers);

        std::string method;
        std::string url;
        std::string http_version;
        int http_version_major;
        int http_version_minor;
        std::string body;

        std::string raw;
        http_request_header headers;
    };
}

#endif //HTTP_HTTP_REQUEST_H
