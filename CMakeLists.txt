cmake_minimum_required(VERSION 3.16)
project(server)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstandalone-debug")

add_executable(server main.cpp server_config.cpp server_config.h cache_file_pool.cpp cache_file_pool.h http/http_request.cpp http/http_request.h http/http_response.cpp http/http_response.h http/http_server.cpp http/http_server.h server_router.cpp server_router.h)

