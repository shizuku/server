/***********************
 * @file: error.cpp
 * @author: shizuku
 * @date: 2020/7/18
 ***********************/
#include "error.h"

const char *http::not_found::what() const noexcept {
    return "404: not found";
}

const char *http::forbidden::what() const noexcept {
    return "403: forbidden";
}
