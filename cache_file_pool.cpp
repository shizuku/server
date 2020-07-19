/***********************
 * @file: cache_file_pool.cpp
 * @author: shizuku
 * @date: 2020/7/16
 ***********************/

#include "cache_file_pool.h"

cache_file::cache_file(const std::string &full_absolute_path, time_t create_time, time_t spire_time)
        : absolute_path{(full_absolute_path)}, expires_time(spire_time), create_time(create_time) {
    load(create_time);

    int start = 0;
    int pos = full_absolute_path.find('/', start);
    while (pos != std::string::npos) {
        start = pos + 1;
        pos = full_absolute_path.find('/', start);
    }
    file_name = full_absolute_path.substr(start);

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

void cache_file::load(time_t now) {
    delete []content;
    if (access(absolute_path.c_str(), 00) == -1) {
        throw http::not_found();
    } else if (access(absolute_path.c_str(), 04) == -1) {
        throw http::forbidden();
    }
    std::ifstream fs{absolute_path, std::ios_base::in | std::ios_base::binary};
    fs.seekg(0, std::ifstream::end);
    length = fs.tellg();
    fs.seekg(0, std::ifstream::beg);
    content = new char[length + 1]{0};
    fs.read(content, length);
    fs.close();
    create_time = now;
}

cache_file::~cache_file() {
    //delete[] content;
}

std::string cache_file::generate_mime_type(const std::string &extension) {
    if (extension == "txt") {//text
        return "text/plain";
    } else if (extension == "htm" || extension == "html") {
        return "text/html";
    } else if (extension == "css") {
        return "text/css";
    } else if (extension == "jpg" || extension == "jpeg") {//image
        return "image/jpeg";
    } else if (extension == "png") {
        return "image/png";
    } else if (extension == "gif") {
        return "image/gif";
    } else if (extension == "bmp") {
        return "image/bmp";
    } else if (extension == "swf") {
        return "image/swf";
    } else if (extension == "svg") {
        return "image/svg+xml";
    } else if (extension == "ico") {
        return "image/x-icon";
    } else if (extension == "mp3") {//audio
        return "audio/mp3";
    } else if (extension == "wav") {
        return "audio/wave";
    } else if (extension == "ogg") {
        return "audio/ogg";
    } else if (extension == "mp4") {//video
        return "video/mp4";
    } else if (extension == "js") {//application
        return "application/javascript";
    } else if (extension == "json") {
        return "application/json";
    } else {
        return "application/octet-stream";
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
            auto t = std::time(nullptr);
            if (f.create_time + f.expires_time > t) {
                f.load(t);
            }
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
