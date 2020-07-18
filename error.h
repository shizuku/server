/***********************
 * @file: error.h
 * @author: shizuku
 * @date: 2020/7/18
 ***********************/
#ifndef SERVER_ERROR_H
#define SERVER_ERROR_H

#include <exception>

class http_error : public std::exception {

};

class file_not_found : public http_error {
public:
    [[nodiscard]] const char *what() const noexcept override;

    static const int code = 404;
};

class forbidden : public http_error {
public:
    [[nodiscard]] const char *what() const noexcept override;

    static const int code = 403;
};

#endif //SERVER_ERROR_H
