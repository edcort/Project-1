#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "BitOutputStream.hpp"

using namespace std;
using namespace testing;

TEST(BitOutputStreamTests, SIMPLE_TEST_1) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(1);
    bos.flush();

    string bitsStr = "10000000";
    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}

TEST(BitOutputStreamTests, SIMPLE_TEST_2) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(0);
    bos.flush();

    string bitsStr = "00000000";
    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}

TEST(BitOutputStreamTests, SIMPLE_TEST_3) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(127);
    bos.writeBit(127);
    bos.writeBit(127);
    bos.writeBit(127);
    bos.writeBit(127);
    bos.writeBit(127);
    bos.writeBit(127);

    bos.flush();

    string bitsStr = "11111110";
    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}

TEST(BitOutputStreamTests, SIMPLE_TEST_4) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(127);
    bos.writeBit(127);
    bos.writeBit(127);
    bos.writeBit(127);
    bos.writeBit(127);
    bos.writeBit(127);
    bos.writeBit(127);
    bos.writeBit(0);
    bos.writeBit(0);

    string bitsStr = "11111110";
    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}

TEST(BitOutputStreamTests, SIMPLE_TEST_5) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(1);
    bos.writeBit(1);
    bos.writeBit(1);
    bos.writeBit(1);
    bos.writeBit(1);
    bos.writeBit(1);
    bos.writeBit(1);

    bos.flush();

    string bitsStr = "11111110";
    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}