#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "BitInputStream.hpp"

using namespace std;
using namespace testing;

TEST(BitInputStreamTests, SIMPLE_TEST_1) {
    string byteStr = "10000000";
    char byte = (char)stoi(byteStr, nullptr, 2);

    stringstream ss;
    ss.write(&byte, 1);
    BitInputStream bis(ss);

    ASSERT_EQ(1, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
}

TEST(BitInputStreamTests, SIMPLE_TEST_2) {
    string byteStr = "10010001";
    char byte = (char)stoi(byteStr, nullptr, 2);

    stringstream ss;
    ss.write(&byte, 1);
    BitInputStream bis(ss);

    ASSERT_EQ(1, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(1, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(1, bis.readBit());
}

TEST(BitInputStreamTests, SIMPLE_TEST_3) {
    string byteStr = "10010001";
    char byte = (char)stoi(byteStr, nullptr, 2);

    stringstream ss;
    ss.write(&byte, 1);
    BitInputStream bis(ss);

    byteStr = "11110000";
    byte = (char)stoi(byteStr, nullptr, 2);
    ss.write(&byte, 1);

    ASSERT_EQ(1, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(1, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(1, bis.readBit());

    ASSERT_EQ(1, bis.readBit());
    ASSERT_EQ(1, bis.readBit());
    ASSERT_EQ(1, bis.readBit());
    ASSERT_EQ(1, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
    ASSERT_EQ(0, bis.readBit());
}