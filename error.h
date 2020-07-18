/***********************
 * @file: error.h
 * @author: shizuku
 * @date: 2020/7/18
 ***********************/
#ifndef SERVER_ERROR_H
#define SERVER_ERROR_H

#include <exception>

class error_file_not_found : public std::exception {
public:
    const char *what() const noexcept override;

    static const int code = 404;
};

#endif //SERVER_ERROR_H
