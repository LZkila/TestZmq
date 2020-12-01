#include "WsUtil.h"
#include <cassert>

HttpClient::HttpClient() {

}

int HttpClient::Get(const std::string &url, std::string &repData) {
    return HttpRet_Ok;
} 

int HttpClient::Post(const std::string &url, const std::string &reqData, std::string &repData) {
    return HttpRet_Ok;
}

int HttpClient::Download(const std::string &url) {
    return HttpRet_Ok;
}

int HttpClient::Upload(const std::string &url, const std::string &filename) {
    return HttpRet_Ok;
}

WsClient::WsClient(const std::string &url) {

}

void WsClient::SetTimeOut(int timeout) {

}

bool WsClient::Connect() {
    return false;
}

void WsClient::Disconnect() {

}

int WsClient::Send(const std::string &reqData, std::string &repData) {
    return HttpRet_Ok;
}

HttpServer::HttpServer(const std::string &ip, int port, bool enableSsl) {

}

void HttpServer::SetHandler(const FUNC_HTTP_DATA_HANDLER &handler) {
    handler_ = handler;
}

WsServer::WsServer(const std::string &ip, int port, bool enableSsl) {

}

void WsServer::SetHandler(const FUNC_WS_DATA_HANDLER &handler) {
    handler_ = handler;
}
