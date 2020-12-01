#pragma once
#include <string>
#include <functional>

typedef std::function<int(const std::string &reqData, std::string &repData)> FUNC_HTTP_DATA_HANDLER;
typedef std::function<int(const std::string &reqData, std::string &repData)> FUNC_WS_DATA_HANDLER;

enum HttpRet {
    HttpRet_Ok = 200,
    HttpRet_NotFound = 404
};

class HttpClient {
public:
    HttpClient();
    ~HttpClient()=default;
    void SetTimeOut(int timeout);

    int Get(const std::string &url, std::string &repData); 
    int Post(const std::string &url, const std::string &reqData, std::string &repData);
    int Download(const std::string &url);
    int Upload(const std::string &url, const std::string &filename);

private:
    int timeout_;
};

class WsClient {
public:
    WsClient(const std::string &url);
    ~WsClient() = default;
    void SetTimeOut(int timeout);
    bool Connect();
    void Disconnect();
    int Send(const std::string &reqData, std::string &repData);

private:
    std::string url_;
    int timeout_;
};

class HttpServer {
public:
    HttpServer(const std::string &ip, int port, bool enableSsl = false);
    ~HttpServer() = default;
    void SetHandler(const FUNC_HTTP_DATA_HANDLER &handler);

private:
    HttpServer() = default;
    
    FUNC_HTTP_DATA_HANDLER handler_;
    std::string ip_;
    int port_;
    bool enableSsl_;
};

class WsServer {
public:
    WsServer(const std::string &ip, int port, bool enableSsl = false);
    ~WsServer() = default;
    void SetHandler(const FUNC_WS_DATA_HANDLER &handler);

private:
    WsServer() = default;
    
    FUNC_WS_DATA_HANDLER handler_;
    std::string ip_;
    int port_;
    bool enableSsl_;
};