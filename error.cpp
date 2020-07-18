/***********************
 * @file: error.cpp
 * @author: shizuku
 * @date: 2020/7/18
 ***********************/
#include "error.h"

const char *file_not_found::what() const noexcept {
    return "404: file not been found";
}

const char *forbidden::what() const noexcept {
    return "403: forbidden";
}
