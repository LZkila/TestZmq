#include "TestZmq.h"
#include <thread>
#include <glog/logging.h>
#include "zmq/ZmqUtil.h"
#include <zmq.h>

using namespace std;

void RunZmqReqClient() {
    ZmqReqClient c(30005);
    for (int i = 0; i < 10; ++i) {
        ZmqReqData req(i, string("hello") + to_string(i));
        ZmqRepData rep;
        c.SendAndWait(req, rep);
    }
}

void RunZmqReqServer() {
    ZmqRepServer s(30005);
    s.RunLoop();
}

TestZmq::TestZmq() {

}

TestZmq::~TestZmq() {

}

void TestZmq::SetUp() {

}

void TestZmq::TearDown() {

}

TEST_F(TestZmq, zmq) {
    thread t1(RunZmqReqServer);
    thread t2(RunZmqReqClient);
    t1.join();
    t2.join();
}