#ifndef STACK_H
#define STACK_H

#include <stdexcept>

// #include "../list/s21_list.h"

// namespace s21 {

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

  //   Stack() : list_(new s21::list<value_type>) {};
  //   Stack(const Stack &s) : list_(new s21::list<value_type>(*(s.list_))) {};
  //   Stack(Stack &&s) : list_(new
  //   s21::list<value_type>(std::move(*(s.list_)))) {}; ~Stack();
  //   Stack<value_type> &operator=(Stack &&s);

  // void push(const_reference value);
  // void pop();
  // void swap(Stack &other);

  // template <typename... Args>
  // void insert_many_back(Args &&...args);

  // template <typename value_type>
  // Stack<value_type>::~Stack() {
  //   delete list_;
  // }

  // template <typename value_type>
  // Stack<value_type> &Stack<value_type>::operator=(Stack &&s) {
  //   list_ = *(s.list_);
  //   return *this;
  // }

  void Clear() {
    while (!Empty()) Pop();
  }

  void Push(const T &value) {
    top_ = new Node(value, top_);
    ++size_;
  }

  void Pop() {
    if (Empty()) throw std::out_of_range("Stack is empty");
    Node *temp = top_;
    top_ = top_->next;
    delete temp;
    --size_;
  }

  const_reference Top() const {
    if (Empty()) throw std::out_of_range("Stack is empty");
    return top_->data;
  }

  bool Empty() const { return top_ == nullptr; }

  size_type Size() const { return size_; }

  // template <typename value_type>
  // typename Stack<value_type>::const_reference Stack<value_type>::top() {
  //   return list_->back();
  // };

  // template <typename value_type>
  // bool Stack<value_type>::Empty() {
  //   return list_->Empty();
  // }

  // template <typename value_type>
  // typename Stack<value_type>::size_type Stack<value_type>::Size() {
  //   return list_->Size();
  // }

  // template <typename value_type>
  // void Stack<value_type>::push(const_reference value) {
  //   list_->push_back(value);
  // }

  // template <typename value_type>
  // void Stack<value_type>::pop() {
  //   list_->pop_back();
  // }

  // template <typename value_type>
  // void Stack<value_type>::swap(Stack &other) {
  //   list_->swap(*(other.list_));
  // }

  // template <typename T>
  // template <typename... Args>
  // void Stack<T>::insert_many_back(Args &&...args) {
  //   list_->insert_many_back(std::forward<Args>(args)...);
  // }
};
// }  // namespace s21

#endif  // STACK_H