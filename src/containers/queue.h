#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template <typename T>
class Queue {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  struct Node {
    T data;
    Node *next;
    Node(const T &value) : data(value), next(nullptr) {}
  };

  Node *front_;
  Node *back_;
  size_t size_;

 public:
  Queue() : front_(nullptr), back_(nullptr), size_(0) {}
  ~Queue() { Clear(); }

  void Push(const T &value) {
    Node *new_node = new Node(value);
    if (Empty()) {
      front_ = new_node;
    } else {
      back_->next = new_node;
    }
    back_ = new_node;
    ++size_;
  }

  const_reference Pop() {
    if (Empty()) throw std::out_of_range("Queue is empty");
    reference back = back_->data;
    Node *temp = front_;
    front_ = front_->next;
    if (front_ == nullptr) back_ = nullptr;
    delete temp;
    --size_;

    return back;
  }

  const_reference Front() const {
    if (Empty()) throw std::out_of_range("Queue is empty");
    return front_->data;
  }

  const_reference Back() const {
    if (Empty()) throw std::out_of_range("Queue is empty");
    return back_->data;
  }

  bool Empty() const { return front_ == nullptr; }
  size_t Size() const { return size_; }

  void Clear() {
    while (!Empty()) Pop();
  }
};

#endif
