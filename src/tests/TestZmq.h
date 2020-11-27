#pragma once
#include <gtest/gtest.h>

class TestZmq : public ::testing::Test {
public:
    TestZmq();
    ~TestZmq() override;
private:
    void SetUp() override;
    void TearDown() override;
};