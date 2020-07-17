/***********************
 * @file: cache_file_pool.cpp
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/
#include "cache_file_pool.h"

cache_file::cache_file(const std::string &full_absolute_path, time_t create_time, time_t spire_time)
        : absolute_path{(full_absolute_path)}, expires_time(spire_time), create_time(create_time) {
    std::ifstream fs{full_absolute_path, std::ios_base::in | std::ios_base::binary};
    std::string str{};
    char buffer[BUFFER_SIZE];
    while (!fs.eof()) {
        ::memset(buffer, 0, BUFFER_SIZE);
        fs.read(buffer, BUFFER_SIZE);
        str.append(buffer);
    }
    content = new char[str.length() + 1]{0};
    ::strcpy(content, str.c_str());

    int pos = 0;
    int start = 0;
    pos = full_absolute_path.find('/', start);
    while (pos != std::string::npos) {
        start = pos + 1;
        pos = full_absolute_path.find('/', start);
    }
    file_name = full_absolute_path.substr(start);

    pos = 0;
    start = 0;
    pos = file_name.find('.', start);
    while (pos != std::string::npos) {
        start = pos + 1;
        pos = file_name.find('.', start);
    }
    file_name_no_extension = file_name.substr(0, start - 1);
    extension = file_name.substr(start);

    mime_type = generate_mime_type(extension);
}

cache_file::~cache_file() {
    //delete[] content;
}

std::string cache_file::generate_mime_type(const std::string &extension) {
    if (extension == "txt") {
        return "text/plain";
    }
    if (extension == "htm") {
        return "text/html";
    }
    if (extension == "html") {
        return "text/html";
    }
    if (extension == "css") {
        return "text/css";
    }
    if (extension == "jpg") {
        return "image/jpg";
    }
    if (extension == "txt") {
        return "text/plain";
    } else {
        return "";
    }
}


cache_file_pool::cache_file_pool(const std::map<std::string, std::string> &expires_rules) : files{}, _expires_rules{} {
    for (auto &i:expires_rules) {
        auto t = time_str_to_mill(i.second);
        int pos = 0;
        int start = 0;
        pos = i.first.find('|', start);
        while (pos != std::string::npos) {
            _expires_rules.insert_or_assign(i.first.substr(start, pos - start), t);
            start = pos + 1;
            pos = i.first.find('|', start);
        }
    }
}

const cache_file &cache_file_pool::get(const std::string &full_absolute_path) {
    for (auto &f:files) {
        if (f.absolute_path == full_absolute_path) {
            return f;
        }
    }
    auto t = std::time(nullptr);
    auto f = cache_file(full_absolute_path, t, 60000);
    try {
        f.expires_time = _expires_rules.at(f.extension);
    } catch (const std::out_of_range &e) {
        f.expires_time = 60000;
    }
    files.push_back(f);
    return get(full_absolute_path);
}

time_t cache_file_pool::time_str_to_mill(const std::string &t) {
    time_t n = 0;
    for (auto &i:t) {
        if (i <= '9' && i >= '0') {
            n = n * 10 + (i - 48);
        } else if (i == 'm') {
            n *= 60;
        } else if (i == 'h') {
            n *= 3600;
        } else if (i == 'd') {
            n *= 86400;
        }
    }
    return n;
}
