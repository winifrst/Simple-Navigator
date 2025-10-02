#include "Stack.hpp"

/**
 * Конструктор по умолчанию. Инициализирует пустой стек
 */
Stack::Stack() : top_(nullptr), size_(0) {}

/**
 * Деструктор. Освобождает всю память, занятую элементами стека
 */
Stack::~Stack() { Clear(); }

/**
 * Добавляет элемент на вершину стека
 * @param value значение для добавления
 */
void Stack::Push(int value) {
  top_ = new Node(value, top_);
  ++size_;
}

/**
 * Удаляет и возвращает элемент с вершины стека
 * @return значение удаленного элемента
 */
int Stack::Pop() {
  if (Empty()) throw std::out_of_range("Stack is empty");

  Node* temp = top_;
  int value = top_->data;
  top_ = top_->next;
  delete temp;
  --size_;

  return value;
}

/**
 * Возвращает элемент с вершины стека без его удаления
 * @return значение верхнего элемента
 */
int Stack::Top() const {
  if (Empty()) throw std::out_of_range("Stack is empty");
  return top_->data;
}

/**
 * Проверяет, является ли стек пустым
 * @return true если стек пуст, false в противном случае
 */
bool Stack::Empty() const { return top_ == nullptr; }

/**
 * Возвращает количество элементов в стеке
 * @return размер стека
 */
size_t Stack::Size() const { return size_; }

/**
 * Очищает стек, удаляя все элементы
 */
void Stack::Clear() {
  while (!Empty()) Pop();
}
