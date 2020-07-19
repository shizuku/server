/***********************
 * @file: main.cpp
 * @author: shizuku
 * @date: 2020/7/15
 ***********************/
#include <iostream>
#include <iomanip>

#include "server_config.h"
#include "http/server.h"
#include "server_router.h"
#include "cache_file_pool.h"
#include "proxy_passer.h"

server_config *sc;
server_router *router;
proxy_passer *passer;
cache_file_pool *file_pool;

void www(const http::request &req, http::response res) {
    std::cout << req.method << "\t" << req.url << std::endl;

    if (!passer->pass(req, res)) {
        auto t = std::time(nullptr);
        std::stringstream tt{};
        tt << std::put_time(std::gmtime(&t), "%c %Z");
        auto time = tt.str();

        try {
            auto path = router->route(req.url);

            auto s = file_pool->get(path);
            res.write_head(200, "OK", http::response_headers{std::map<std::string, std::string>{
                    {"Date",           time},
                    {"Accept-Ranges",  "bytes"},
                    {"Content-Type",   s.mime_type},
                    {"Content-Length", std::to_string(s.length)},
                    {"Server",         "shizuku/0.1"},
            }});
            res.write(s.content, s.length);
        } catch (const http::not_found &e) {
            auto s = file_pool->get(sc->error_pages["404"]);
            res.write_head(404, "Not Found", http::response_headers{std::map<std::string, std::string>{
                    {"Date",           time},
                    {"Accept-Ranges",  "bytes"},
                    {"Content-Type",   s.mime_type},
                    {"Content-Length", std::to_string(s.length)},
                    {"Server",         "shizuku/0.1"},
            }});
            res.write(s.content, s.length);
        } catch (const http::forbidden &e) {
            auto s = file_pool->get(sc->error_pages["403"]);
            res.write_head(403, "Forbidden", http::response_headers{std::map<std::string, std::string>{
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
}

int main() {
    signal(SIGPIPE, SIG_IGN);
    const std::string config_filename = "config.json";

    sc = new server_config(config_filename);
    router = new server_router(static_cast<std::map<std::string, std::string, cmp> &&>(sc->router));
    passer = new proxy_passer(
            static_cast<std::map<std::string, std::map<std::string, std::string>, cmp> &&>(sc->proxy_pass));
    file_pool = new cache_file_pool{sc->expires};

    http::create_server(&www).listen(sc->port);

    delete sc;
    delete router;
    delete passer;
    delete file_pool;

    return 0;
}
