/***********************
 * @file: main.cpp
 * @author: shizuku
 * @date: 2020/7/15
 ***********************/
#include <iostream>
#include <iomanip>

#include "server_config.h"
#include "http/http_server.h"
#include "server_router.h"
#include "cache_file_pool.h"

server_config *sc;
server_router *router;
cache_file_pool *file_pool;

void www(const http::http_request &req, http::http_response res) {
    std::cout << req.method << "\t" << req.url << std::endl;

    auto t = std::time(nullptr);
    std::stringstream tt{};
    tt << std::put_time(std::gmtime(&t), "%c %Z");
    auto time = tt.str();

    try {
        auto path = router->route(req.url);

        auto s = file_pool->get(path);
        res.write_head(200, "OK", http::http_response_headers{std::map<std::string, std::string>{
                {"Date",           time},
                {"Accept-Ranges",  "bytes"},
                {"Content-Type",   s.mime_type},
                {"Content-Length", std::to_string(s.length)},
                {"Server",         "shizuku/0.1"},
        }});
        res.write(s.content, s.length);
    } catch (const file_not_found &e) {
        auto s = file_pool->get(sc->error_pages["404"]);
        res.write_head(404, "Not Found", http::http_response_headers{std::map<std::string, std::string>{
                {"Date",           time},
                {"Accept-Ranges",  "bytes"},
                {"Content-Type",   s.mime_type},
                {"Content-Length", std::to_string(s.length)},
                {"Server",         "shizuku/0.1"},
        }});
        res.write(s.content, s.length);
    } catch (const forbidden &e) {
        auto s = file_pool->get(sc->error_pages["403"]);
        res.write_head(403, "Forbidden", http::http_response_headers{std::map<std::string, std::string>{
                {"Date",           time},
                {"Accept-Ranges",  "bytes"},
                {"Content-Type",   s.mime_type},
                {"Content-Length", std::to_string(s.length)},
                {"Server",         "shizuku/0.1"},
        }});
        res.write(s.content, s.length);
    }
    res.shutdown();
}

int main() {
    const std::string config_filename = "config.json";

    sc = new server_config(config_filename);
    router = new server_router(static_cast<std::map<std::string, std::string, cmp> &&>(sc->router));
    file_pool = new cache_file_pool{sc->expires};

    http::create_server(&www).listen(sc->port);

    delete sc;
    delete router;
    delete file_pool;

    return 0;
}
