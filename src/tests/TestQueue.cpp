#include <gtest/gtest.h>

#include "../containers/Queue.hpp"

TEST(QueueTest, DefaultConstructor) {
  Queue queue;
  EXPECT_TRUE(queue.Empty());
  EXPECT_EQ(queue.Size(), static_cast<const unsigned long>(0));
}

TEST(QueueTest, Push) {
  Queue queue;
  queue.Push(1);
  EXPECT_FALSE(queue.Empty());
  EXPECT_EQ(queue.Size(), static_cast<const unsigned long>(1));
  EXPECT_EQ(queue.Front(), 1);
  EXPECT_EQ(queue.Back(), 1);
}

TEST(QueueTest, Pop) {
  Queue queue;
  queue.Push(1);
  queue.Push(2);
  queue.Pop();
  EXPECT_EQ(queue.Size(), static_cast<const unsigned long>(1));
  EXPECT_EQ(queue.Front(), 2);
  queue.Pop();
  EXPECT_TRUE(queue.Empty());
}

TEST(QueueTest, Front) {
  Queue queue;
  queue.Push(1);
  EXPECT_EQ(queue.Front(), 1);
  queue.Push(2);
  EXPECT_EQ(queue.Front(), 1);
}

TEST(QueueTest, Back) {
  Queue queue;
  queue.Push(1);
  EXPECT_EQ(queue.Back(), 1);
  queue.Push(2);
  EXPECT_EQ(queue.Back(), 2);
}

TEST(QueueTest, Empty) {
  Queue queue;
  EXPECT_TRUE(queue.Empty());
  queue.Push(1);
  EXPECT_FALSE(queue.Empty());
}

TEST(QueueTest, Clear) {
  Queue queue;
  queue.Push(1);
  queue.Push(2);
  queue.Clear();
  EXPECT_TRUE(queue.Empty());
  EXPECT_EQ(queue.Size(), static_cast<const unsigned long>(0));
}

TEST(QueueTest, PopEmpty) {
  Queue queue;
  EXPECT_THROW(queue.Pop(), std::out_of_range);
}

TEST(QueueTest, FrontEmpty) {
  Queue queue;
  EXPECT_THROW(queue.Front(), std::out_of_range);
}

TEST(QueueTest, BackEmpty) {
  Queue queue;
  EXPECT_THROW(queue.Back(), std::out_of_range);
}
