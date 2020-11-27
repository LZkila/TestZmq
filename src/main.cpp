#include <iostream>
#include <glog/logging.h>
#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
    FLAGS_logtostderr = 1;
    google::InitGoogleLogging(argv[0]);
    LOG(INFO) << "hello world";
    ::testing::InitGoogleTest(&argc, argv);
    auto ret = RUN_ALL_TESTS();
    return ret;
}