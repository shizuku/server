/***********************
 * @file: cache_file_pool.h
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/
#ifndef SERVER_CACHE_FILE_POOL_H
#define SERVER_CACHE_FILE_POOL_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <bitset>
#include <sstream>
#include <cstring>
#include <ctime>

#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include "error.h"

class cache_file {
public:
    const int BUFFER_SIZE = 40960;

    cache_file(const std::string &full_absolute_path, time_t create_time, time_t spire_time);

    ~cache_file();

    static std::string generate_mime_type(const std::string &extension);

    std::string absolute_path;
    std::string file_name;
    std::string file_name_no_extension;
    std::string extension;
    std::string mime_type;

    time_t expires_time;
    time_t create_time;

    char *content;
    size_t length;
};

class cache_file_pool {
public:
    explicit cache_file_pool(const std::map<std::string, std::string> &expires_rules);

    const cache_file &get(const std::string &full_absolute_path);

    static time_t time_str_to_mill(const std::string &t);

private:
    std::vector<cache_file> files;
    std::map<std::string, time_t> _expires_rules;
};

#endif //SERVER_CACHE_FILE_POOL_H
