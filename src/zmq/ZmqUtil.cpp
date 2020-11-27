#include "ZmqUtil.h"
#include <cassert>
#include <sstream>
#include <thread>
#include <chrono>
#include <zmq.hpp>
#include <msgpack.hpp>
#include <fmt/format.h>
#include <glog/logging.h>

using namespace std;
using namespace fmt;

ZmqReqClient::ZmqReqClient(int port) {
    Init("", port);
}

ZmqReqClient::ZmqReqClient(const std::string &ip, int port) {
    Init(ip, port);
}

bool ZmqReqClient::SendAndWait(const ZmqReqData &data, ZmqRepData &repData) {
    assert(sock_);

    msgpack::type::tuple<int, std::string> src(data.type, data.data);
    stringstream buf;
    msgpack::pack(buf, src);
    zmq::message_t msg(buf.str());

    LOG(INFO) << "client send";
    try {
        sock_->send(msg, zmq::send_flags::none);
    } catch (zmq::error_t e) {
        LOG(WARNING) << "zmq send failed:" << e.what();
        return false;
    }

    LOG(INFO) << "client recv";
    zmq::message_t recvmsg;
    try {
        sock_->recv(recvmsg);
    } catch (zmq::error_t e) {
        LOG(WARNING) << "zmq send failed:" << e.what();
        return false;
    }

    LOG(INFO) << "client recv suc";
    auto oh = msgpack::unpack(static_cast<const char*>(recvmsg.data()), recvmsg.size());
    auto obj = oh.get();
    auto dst = obj.as<msgpack::type::tuple<int, int, std::string>>();
    repData.type = dst.get<0>();
    repData.ret = dst.get<1>();
    repData.data = dst.get<2>();

    LOG(INFO) << "client: type:" << repData.type << " ret:" << repData.ret << " data:" << repData.data;
    return true;
}

void ZmqReqClient::Init(const std::string &ip, int port) {
    ctx_ = shared_ptr<zmq::context_t>(new zmq::context_t());
    sock_ = shared_ptr<zmq::socket_t>(new zmq::socket_t(*ctx_, zmq::socket_type::req));
    sock_->connect(format("tcp://{}:{}", ip.empty() ? "127.0.0.1" : ip, port));
}

ZmqRepServer::ZmqRepServer(int port) {
    Init("", port);
}

ZmqRepServer::ZmqRepServer(const std::string &ip, int port) {
    Init(ip, port);
}

void ZmqRepServer::SetHandler(const FUNC_ZMQ_REQ_DATA_HANDLER &handler) {
    handler_ = handler;
}

void ZmqRepServer::RunLoop() {
    assert(sock_);
    while (true) {
        zmq::message_t req;
        try {
            sock_->recv(req);
        } catch (zmq::error_t e) {
            LOG(WARNING) << "zmq recv failed:" << e.what();
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }

        auto oh = msgpack::unpack(static_cast<const char*>(req.data()), req.size());
        auto obj = oh.get();
        auto dst = obj.as<msgpack::type::tuple<int, std::string>>();
        ZmqReqData reqData;
        reqData.type = dst.get<0>();
        reqData.data = dst.get<1>();

        LOG(INFO) << "server: type:" << reqData.type << " data:" << reqData.data;

        msgpack::type::tuple<int, int, std::string> src(reqData.type, 0, reqData.data);
        stringstream buf;
        msgpack::pack(buf, src);
        zmq::message_t msg(buf.str());
        try {
            sock_->send(msg, zmq::send_flags::none);
        } catch (zmq::error_t e) {
            LOG(WARNING) << "zmq send failed:" << e.what();
            continue;
        }
    }  
}

void ZmqRepServer::Init(const std::string &ip, int port) {
    ctx_ = shared_ptr<zmq::context_t>(new zmq::context_t());
    sock_ = shared_ptr<zmq::socket_t>(new zmq::socket_t(*ctx_, zmq::socket_type::rep));
    sock_->bind(format("tcp://{}:{}", ip.empty() ? "127.0.0.1" : ip, port));
}
