#include <gtest/gtest.h>

#include "../containers/Stack.hpp"

TEST(StackTest, DefaultConstructor) {
  Stack stack;
  EXPECT_TRUE(stack.Empty());
  EXPECT_EQ(stack.Size(), 0);
}

TEST(StackTest, Push) {
  Stack stack;
  stack.Push(1);
  EXPECT_FALSE(stack.Empty());
  EXPECT_EQ(stack.Size(), 1);
  EXPECT_EQ(stack.Top(), 1);
}

TEST(StackTest, Pop) {
  Stack stack;
  stack.Push(1);
  stack.Push(2);
  stack.Pop();
  EXPECT_EQ(stack.Size(), 1);
  EXPECT_EQ(stack.Top(), 1);
  stack.Pop();
  EXPECT_TRUE(stack.Empty());
}

TEST(StackTest, Top) {
  Stack stack;
  stack.Push(1);
  EXPECT_EQ(stack.Top(), 1);
  stack.Push(2);
  EXPECT_EQ(stack.Top(), 2);
}

TEST(StackTest, Empty) {
  Stack stack;
  EXPECT_TRUE(stack.Empty());
  stack.Push(1);
  EXPECT_FALSE(stack.Empty());
}

TEST(StackTest, Clear) {
  Stack stack;
  stack.Push(1);
  stack.Push(2);
  stack.Clear();
  EXPECT_TRUE(stack.Empty());
  EXPECT_EQ(stack.Size(), 0);
}

TEST(StackTest, PopEmpty) {
  Stack stack;
  EXPECT_THROW(stack.Pop(), std::out_of_range);
}

TEST(StackTest, TopEmpty) {
  Stack stack;
  EXPECT_THROW(stack.Top(), std::out_of_range);
}
