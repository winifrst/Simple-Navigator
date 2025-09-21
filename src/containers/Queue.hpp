#pragma once

#include <stdexcept>

class Queue {
 private:
  struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
  };

  Node* front_;
  Node* back_;
  size_t size_;

 public:
  Queue();
  ~Queue();

  void Push(int value);
  int Pop();
  int Front() const;
  int Back() const;
  bool Empty() const;
  size_t Size() const;
  void Clear();
};
