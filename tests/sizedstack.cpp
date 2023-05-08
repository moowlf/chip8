
#include "SizedStack.hpp"
#include <gtest/gtest.h>

TEST(SizedStack, Top) {

  SizedStack<uint16_t, 1> stack;
  EXPECT_THROW(stack.top(), std::runtime_error);

  stack.push(1);
  stack.push(2);

  const uint16_t &test = stack.top();
  EXPECT_EQ(test, 2);
}

TEST(SizedStack, Pop) {

  SizedStack<uint16_t, 1> stack;
  EXPECT_THROW(stack.pop(), std::runtime_error);

  stack.push(1);
  stack.push(2);

  try {
    auto elem = stack.pop();
    EXPECT_EQ(elem, 2);

    elem = stack.pop();
    EXPECT_EQ(elem, 1);

    EXPECT_TRUE(stack.empty());
  } catch (...) {
    FAIL();
  }
}

TEST(SizedStack, Empty) {

  SizedStack<uint16_t, 1> stack;
  EXPECT_TRUE(stack.empty());

  stack.push(1);
  EXPECT_FALSE(stack.empty());
}
