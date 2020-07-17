/***********************
 * @file: http_request.cpp
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/
#include "http_request.h"


http::http_request::http_request(const std::string &request) {
    auto req_line_split = request.find("\r\n");
    auto req_head_split = request.find("\r\n\r\n");
    auto status = request.substr(0, req_line_split);
    auto head = request.substr(req_line_split + 2, req_head_split - req_line_split - 2);
    body = request.substr(req_head_split + 4);

    auto line_split = status.find(' ');
    method = status.substr(0, line_split);
    status = status.substr(line_split + 1);

    line_split = status.find(' ');
    url = status.substr(0, line_split);
    status = status.substr(line_split + 1);

    line_split = status.find("HTTP/");
    http_version = status.substr(line_split + 5);

    auto version_split = http_version.find('.');
    auto major_str = http_version.substr(0, version_split);
    auto minor_str = http_version.substr(version_split + 1);
    for (auto &i:major_str) {
        http_version_major = http_version_major * 10 + (i - 48);
    }
    for (auto &i:minor_str) {
        http_version_minor = http_version_minor * 10 + (i - 48);
    }

    headers = http_request_header{head};
}

http::http_request_header::http_request_header(const std::string &head) : raw{}, map{} {
    unsigned long start = 0;
    auto pos = head.find("\r\n", start);
    while (pos != std::string::npos) {
        auto str = head.substr(start, pos - start);
        auto split = str.find(": ");
        auto first = str.substr(0, split);
        auto second = str.substr(split + 2);
        raw.push_back(str);
        map.insert_or_assign(first, second);
        start = pos + 2;
        pos = head.find("\r\n", start);
    }
}

http::http_request_header::http_request_header() : http_request_header{""} {}
