#pragma once

#include <stdexcept>

class Stack {
 private:
  struct Node {
    int data;
    Node* next;
    Node(int value, Node* next_node = nullptr) : data(value), next(next_node) {}
  };

  Node* top_;
  size_t size_;

 public:
  Stack();
  ~Stack();

  void Push(int value);
  int Pop();
  int Top() const;
  bool Empty() const;
  size_t Size() const;
  void Clear();
};
