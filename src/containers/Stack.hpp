#pragma once

#include <stdexcept>

// ToDo Добавить doxygen документацию

template <typename T>
class Stack {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  struct Node {
    value_type data;
    Node *next;
    Node(const T &value, Node *next_node = nullptr)
        : data(value), next(next_node) {}
  };

  Node *top_;
  size_type size_;

 public:
  Stack() : top_(nullptr), size_(0) {}
  ~Stack() { Clear(); }

  void Clear() {
    while (!Empty()) Pop();
  }

  void Push(const value_type &value) {
    top_ = new Node(value, top_);
    ++size_;
  }

  value_type Pop() {
    if (Empty()) throw std::out_of_range("Stack is empty");

    Node *temp = top_;
    value_type value = top_->data;
    top_ = top_->next;
    delete temp;
    --size_;

    return value;
  }

  const_reference Top() const {
    if (Empty()) throw std::out_of_range("Stack is empty");
    return top_->data;
  }

  bool Empty() const { return top_ == nullptr; }

  size_type Size() const { return size_; }
};