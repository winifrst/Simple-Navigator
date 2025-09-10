#include "../containers/queue.h"

#include <gtest/gtest.h>

TEST(QueueTest, DefaultConstructor) {
  Queue<int> queue;
  EXPECT_TRUE(queue.Empty());
  EXPECT_EQ(queue.Size(), 0);
}

TEST(QueueTest, Push) {
  Queue<int> queue;
  queue.Push(1);
  EXPECT_FALSE(queue.Empty());
  EXPECT_EQ(queue.Size(), 1);
  EXPECT_EQ(queue.Front(), 1);
  EXPECT_EQ(queue.Back(), 1);
}

TEST(QueueTest, Pop) {
  Queue<int> queue;
  queue.Push(1);
  queue.Push(2);
  queue.Pop();
  EXPECT_EQ(queue.Size(), 1);
  EXPECT_EQ(queue.Front(), 2);
  queue.Pop();
  EXPECT_TRUE(queue.Empty());
}

TEST(QueueTest, Front) {
  Queue<int> queue;
  queue.Push(1);
  EXPECT_EQ(queue.Front(), 1);
  queue.Push(2);
  EXPECT_EQ(queue.Front(), 1);
}

TEST(QueueTest, Back) {
  Queue<int> queue;
  queue.Push(1);
  EXPECT_EQ(queue.Back(), 1);
  queue.Push(2);
  EXPECT_EQ(queue.Back(), 2);
}

TEST(QueueTest, Empty) {
  Queue<int> queue;
  EXPECT_TRUE(queue.Empty());
  queue.Push(1);
  EXPECT_FALSE(queue.Empty());
}

TEST(QueueTest, Clear) {
  Queue<int> queue;
  queue.Push(1);
  queue.Push(2);
  queue.Clear();
  EXPECT_TRUE(queue.Empty());
  EXPECT_EQ(queue.Size(), 0);
}

TEST(QueueTest, PopEmpty) {
  Queue<int> queue;
  EXPECT_THROW(queue.Pop(), std::out_of_range);
}

TEST(QueueTest, FrontEmpty) {
  Queue<int> queue;
  EXPECT_THROW(queue.Front(), std::out_of_range);
}

TEST(QueueTest, BackEmpty) {
  Queue<int> queue;
  EXPECT_THROW(queue.Back(), std::out_of_range);
}
