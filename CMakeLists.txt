cmake_minimum_required(VERSION 3.16)
project(server)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstandalone-debug")

add_executable(server main.cpp server_config.cpp server_config.h cache_file_pool.cpp cache_file_pool.h http/request.cpp http/request.h http/response.cpp http/response.h http/server.cpp http/server.h server_router.cpp server_router.h http/error.cpp http/error.h server_proxy_passer.cpp server_proxy_passer.h)

