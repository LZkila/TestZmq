#pragma once
#include <string>
#include <functional>
#include <memory>
// #include <zmq.hpp>

struct ZmqReqData {
    int type = 0;
    std::string data;
    ZmqReqData() = default;
    ZmqReqData(int type, const std::string &data) {
        this->type = type;
        this->data = data;
    }
};

struct ZmqRepData {
    int type;
    int ret;
    std::string data;
};

typedef std::function<int(const ZmqReqData &data, ZmqRepData &repData)> FUNC_ZMQ_REQ_DATA_HANDLER; 

namespace zmq {
    class context_t;
    class socket_t;
}

class ZmqReqClient {
public:
    ZmqReqClient(int port);
    ZmqReqClient(const std::string &ip, int port); // if ip empty, then will be localhost
    ~ZmqReqClient() = default;
    bool SendAndWait(const ZmqReqData &data, ZmqRepData &repData);

private:
    ZmqReqClient() = default;
    void Init(const std::string &ip, int port);

    std::shared_ptr<zmq::context_t> ctx_;
    std::shared_ptr<zmq::socket_t> sock_;
};

class ZmqRepServer {
public:
    ZmqRepServer(int port);
    ZmqRepServer(const std::string &ip, int port);
    ~ZmqRepServer() = default;
    void SetHandler(const FUNC_ZMQ_REQ_DATA_HANDLER &handler);
    void RunLoop();

private:
    ZmqRepServer() = default;
    void Init(const std::string &ip, int port);

    FUNC_ZMQ_REQ_DATA_HANDLER handler_;
    std::shared_ptr<zmq::context_t> ctx_;
    std::shared_ptr<zmq::socket_t> sock_;
};