#include "Queue.hpp"

/**
 * Конструктор по умолчанию. Инициализирует пустую очередь
 */
Queue::Queue() : front_(nullptr), back_(nullptr), size_(0) {}

/**
 * Деструктор. Освобождает всю память, занятую элементами очереди
 */
Queue::~Queue() { Clear(); }

/**
 * Добавляет элемент в конец очереди
 * @param value значение для добавления
 */
void Queue::Push(int value) {
  Node *new_node = new Node(value);
  if (Empty()) {
    front_ = new_node;
  } else {
    back_->next = new_node;
  }
  back_ = new_node;
  ++size_;
}

/**
 * Удаляет и возвращает элемент из начала очереди
 * @return значение удаленного элемента
 */
int Queue::Pop() {
  if (Empty()) throw std::out_of_range("Queue is empty");

  int value = front_->data;
  Node *temp = front_;
  front_ = front_->next;

  if (front_ == nullptr) {
    back_ = nullptr;
  }
  delete temp;
  --size_;

  return value;
}

/**
 * Возвращает элемент из начала очереди без его удаления
 * @return значение первого элемента
 */
int Queue::Front() const {
  if (Empty()) throw std::out_of_range("Queue is empty");
  return front_->data;
}

/**
 * Возвращает элемент из конца очереди без его удаления
 * @return значение последнего элемента
 */
int Queue::Back() const {
  if (Empty()) throw std::out_of_range("Queue is empty");
  return back_->data;
}

/**
 * Проверяет, является ли очередь пустой
 * @return true если очередь пуста, false в противном случае
 */
bool Queue::Empty() const { return front_ == nullptr; }

/**
 * Возвращает количество элементов в очереди
 * @return размер очереди
 */
size_t Queue::Size() const { return size_; }

/**
 * Очищает очередь, удаляя все элементы
 */
void Queue::Clear() {
  while (!Empty()) Pop();
}
