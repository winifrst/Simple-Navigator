#include "Queue.hpp"

Queue::Queue() : front_(nullptr), back_(nullptr), size_(0) {}

Queue::~Queue() { Clear(); }

void Queue::Push(int value) {
  Node* new_node = new Node(value);
  if (Empty()) {
    front_ = new_node;
  } else {
    back_->next = new_node;
  }
  back_ = new_node;
  ++size_;
}

int Queue::Pop() {
  if (Empty()) throw std::out_of_range("Queue is empty");

  int value = front_->data;
  Node* temp = front_;
  front_ = front_->next;

  if (front_ == nullptr) {
    back_ = nullptr;
  }
  delete temp;
  --size_;

  return value;
}

int Queue::Front() const {
  if (Empty()) throw std::out_of_range("Queue is empty");
  return front_->data;
}

int Queue::Back() const {
  if (Empty()) throw std::out_of_range("Queue is empty");
  return back_->data;
}

bool Queue::Empty() const { return front_ == nullptr; }

size_t Queue::Size() const { return size_; }

void Queue::Clear() {
  while (!Empty()) Pop();
}
