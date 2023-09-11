#ifndef CPP2_S21_CONTAINERS_2_Stack_S21_Stack_H_
#define CPP2_S21_CONTAINERS_2_Stack_S21_Stack_H_

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T>
class S21Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  S21Stack() : head(nullptr), capacity(0) {}

  S21Stack(std::initializer_list<value_type> const &items)
      : head(nullptr), capacity(0) {
    for (const auto &item : items) push(item);
  }

  S21Stack(const S21Stack &other) : head(nullptr), capacity(0) {
    copyFrom(other);
  }

  S21Stack(S21Stack &&other) : head(other.head), capacity(other.capacity) {
    other.head = nullptr;
    other.capacity = 0;
  }

  ~S21Stack() { clear(); }

  S21Stack<T> &operator=(const S21Stack<T> &other) noexcept {
    if (this != &other) {
      clear();
      copyFrom(other);
    }
    return *this;
  }

  S21Stack<T> &operator=(S21Stack<T> &&other) noexcept {
    if (this != &other) {
      clear();
      head = other.head;
      capacity = other.capacity;
      other.head = nullptr;
      other.capacity = 0;
    }
    return *this;
  }

  const_reference top() const {
    if (empty()) throw std::out_of_range("Stack is empty");
    return head->data;
  }

  bool empty() const { return (capacity == 0); }

  size_type size() const { return capacity; }

  void print() const {
    Node *current = head;
    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }

  void push(const_reference value) {
    Node *new_node = new Node(value);
    new_node->next = head;
    head = new_node;
    capacity++;
  }

  void pop() {
    if (empty()) throw std::out_of_range("Stack is empty");

    Node *temp = head;
    head = head->next;
    delete temp;
    capacity--;
  }

  void swap(S21Stack &other) {
    std::swap(head, other.head);
    std::swap(capacity, other.capacity);
  }

  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  struct Node {
    T data;
    Node *next;

    Node(const T &value) : data(value), next(nullptr) {}
  };
  Node *head;
  size_t capacity;

  void clear() {
    while (head != nullptr) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
    capacity = 0;
  }

  void copyFrom(const S21Stack &other) {
    Node *current_other = other.head;
    Node **current_this = &head;

    while (current_other != nullptr) {
      *current_this = new Node(current_other->data);
      current_this = &((*current_this)->next);
      current_other = current_other->next;
    }

    capacity = other.capacity;
  }
};
template <typename T>
template <typename... Args>
void S21Stack<T>::insert_many_front(Args &&...args) {
  T values[] = {std::forward<Args>(args)...};

  for (const T &value : values) {
    Node *new_node = new Node(value);
    new_node->next = head;
    head = new_node;
    capacity++;
  }
}

}  // namespace s21

#endif /* CPP2_S21_CONTAINERS_1_Stack_S21_Stack_H_ */