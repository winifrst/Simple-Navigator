#include "Stack.hpp"

Stack::Stack() : top_(nullptr), size_(0) {}

Stack::~Stack() { Clear(); }

void Stack::Push(int value) {
  top_ = new Node(value, top_);
  ++size_;
}

int Stack::Pop() {
  if (Empty()) throw std::out_of_range("Stack is empty");

  Node* temp = top_;
  int value = top_->data;
  top_ = top_->next;
  delete temp;
  --size_;

  return value;
}

int Stack::Top() const {
  if (Empty()) throw std::out_of_range("Stack is empty");
  return top_->data;
}

bool Stack::Empty() const { return top_ == nullptr; }

size_t Stack::Size() const { return size_; }

void Stack::Clear() {
  while (!Empty()) Pop();
}
