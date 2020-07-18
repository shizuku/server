# server

#### 介绍
低性能http服务器（大雾）。

#### 软件架构
软件架构说明
1. http::http_request

实现了解析http request 
2. http::http_response

实现了write 、shutdown和end。
3. http::http_server

实现listen监听
4. server_config

使用boost/property_tree/json_parser解析json配置文件
5. server_router

分析url并根据配置路由

6. cache_file

7. error

8. proxy_passer

9.main

#### 使用说明

1. 配置文件
```json
{
  "port": "8000",
  "router": {
    "/": "/home/shizuku/workspace/Webstorm/untitled/build",
  },
  "expires": {
    "htm|html|txt|rar|zip|flv|mid|doc|ppt|pdf|xls|mp3|wma": "15d",
    "js|css|json": "1h",
    "gif|jpg|jpeg|png|bmp|swf|ioc": "10d"
  },
  "error_pages": {
    "404": "error_pages/404.html",
    "403": "error_pages/403.html"
  },
  "proxy_pass": {
    "/hello": {
      "host": "127.0.0.1",
      "port": "9090",
      "url": "/hello"
    }
  }
}
```
2. 生成React页面测试请求和路由

3. 用node测试反向代理
```js
const http = require('http');

let server = http.createServer(function(req, res){
    console.log(req.url);
    res.write("hello");
    res.end();
});

server.listen(9090);
```

