
#include <gtest/gtest.h>

#include <Macros.hpp>


TEST(TestMacros, getLowest8Bits) {

    EXPECT_EQ(getLowest8Bits(0x0A95), 0x0095);
    EXPECT_EQ(getLowest8Bits(0x7A9D), 0x009D);
    EXPECT_EQ(getLowest8Bits(0x0000), 0x0000);
    EXPECT_EQ(getLowest8Bits(0xFFFF), 0x00FF);
}


TEST(TestMacros, getLowest12Bits) {

    EXPECT_EQ(getLowest8Bits(0x0A95), 0x0095);
    EXPECT_EQ(getLowest8Bits(0x7A9D), 0x009D);
    EXPECT_EQ(getLowest8Bits(0x0000), 0x0000);
    EXPECT_EQ(getLowest8Bits(0xFFFF), 0x00FF);
}

TEST(TestMacros, get1stNibble) {

    EXPECT_EQ(get1stNibble(0x8A95), 0x0008);
    EXPECT_EQ(get1stNibble(0x7A9D), 0x0007);
    EXPECT_EQ(get1stNibble(0x0000), 0x0000);
    EXPECT_EQ(get1stNibble(0xFFFF), 0x000F);
}

TEST(TestMacros, get2ndNibble) {

    EXPECT_EQ(get2ndNibble(0x8A95), 0x000A);
    EXPECT_EQ(get2ndNibble(0x7D9D), 0x000D);
    EXPECT_EQ(get2ndNibble(0x0000), 0x0000);
    EXPECT_EQ(get2ndNibble(0xFFFF), 0x000F);
}

TEST(TestMacros, get3rdNibble) {

    EXPECT_EQ(get3rdNibble(0x8A95), 0x0009);
    EXPECT_EQ(get3rdNibble(0x7D8D), 0x0008);
    EXPECT_EQ(get3rdNibble(0x0000), 0x0000);
    EXPECT_EQ(get3rdNibble(0xFFFF), 0x000F);
}

TEST(TestMacros, get4thNibble) {

    EXPECT_EQ(get4thNibble(0x8A95), 0x0005);
    EXPECT_EQ(get4thNibble(0x7D8D), 0x000D);
    EXPECT_EQ(get4thNibble(0x0000), 0x0000);
    EXPECT_EQ(get4thNibble(0xFFFF), 0x000F);
}

TEST(TestMacros, getLSB) {

    EXPECT_EQ(getLSB(0x8A96), false);
    EXPECT_EQ(getLSB(0x7D8D), true);
    EXPECT_EQ(getLSB(0x0000), false);
    EXPECT_EQ(getLSB(0xFFFF), true);
}

TEST(TestMacros, getMSB) {

    EXPECT_EQ(getMSB(0x8A96), true);
    EXPECT_EQ(getMSB(0x7D8D), false);
    EXPECT_EQ(getMSB(0x0000), false);
    EXPECT_EQ(getMSB(0xFFFF), true);
}

TEST(TestMacros, getNthBit) {

    EXPECT_EQ(getNthBit(0x85, 0), true);
    EXPECT_EQ(getNthBit(0x7D, 1), false);
    EXPECT_EQ(getNthBit(0x00, 5), false);
    EXPECT_EQ(getNthBit(0xFF, 7), true);
}
