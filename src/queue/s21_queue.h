#ifndef CPP2_S21_CONTAINERS_2_Queue_S21_Queue_H_
#define CPP2_S21_CONTAINERS_2_Queue_S21_Queue_H_

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T>
class S21Queue {
 public:
  using pointer = T *;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  S21Queue();
  S21Queue(size_type n);
  S21Queue(std::initializer_list<value_type> const &items);
  S21Queue(const S21Queue &l);
  S21Queue(S21Queue &&l);
  ~S21Queue();
  S21Queue<T> &operator=(const S21Queue<T> &other) noexcept;
  S21Queue<T> &operator=(S21Queue<T> &&other) noexcept;

  const_reference front() const { return (head) ? head->data : value_type{}; }
  const_reference back() const { return (tail) ? tail->data : value_type{}; }

  bool empty() const { return (capacity == 0); }
  size_type size() const { return capacity; }

  void clear();
  void print();
  void push(const_reference value);  // inserts element at the end
  void pop();                        // removes the first element
  void swap(S21Queue &other);        // swaps the contents

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  struct Node {
    T data;
    Node *next;
    Node(const T &value) : data(value), next(nullptr) {}
  };

  Node *head;
  Node *tail;
  size_t capacity;
};

template <typename T>
S21Queue<T>::S21Queue() : head(nullptr), tail(nullptr), capacity(0) {}

template <typename T>
S21Queue<T>::S21Queue(size_type n) : head(nullptr), tail(nullptr), capacity(0) {
  for (size_type i = 0; i < n; ++i) {
    push(T{});
  }
}

template <typename T>
S21Queue<T>::S21Queue(std::initializer_list<value_type> const &items)
    : head(nullptr), tail(nullptr), capacity(0) {
  for (const auto &item : items) {
    push(item);
  }
}

template <typename T>
S21Queue<T>::S21Queue(const S21Queue &other)
    : head(nullptr), tail(nullptr), capacity(0) {
  Node *current = other.head;
  while (current) {
    push(current->data);
    current = current->next;
  }
}

template <typename T>
S21Queue<T>::S21Queue(S21Queue &&other)
    : head(other.head), tail(other.tail), capacity(other.capacity) {
  other.head = nullptr;
  other.tail = nullptr;
  other.capacity = 0;
}

template <typename T>
S21Queue<T>::~S21Queue() {
  clear();
}

template <typename T>
S21Queue<T> &S21Queue<T>::operator=(const S21Queue<T> &other) noexcept {
  if (this != &other) {
    clear();
    Node *current = other.head;
    while (current) {
      push(current->data);
      current = current->next;
    }
  }
  return *this;
}

template <typename T>
S21Queue<T> &S21Queue<T>::operator=(S21Queue<T> &&other) noexcept {
  if (this != &other) {
    clear();
    head = other.head;
    tail = other.tail;
    capacity = other.capacity;
    other.head = nullptr;
    other.tail = nullptr;
    other.capacity = 0;
  }
  return *this;
}

template <typename T>
void S21Queue<T>::clear() {
  while (!empty()) {
    pop();
  }
}

template <typename T>
void S21Queue<T>::print() {
  Node *current = head;
  while (current) {
    std::cout << current->data << " ";
    current = current->next;
  }
  std::cout << std::endl;
}

template <typename T>
void S21Queue<T>::push(const_reference value) {
  Node *newNode = new Node(value);
  if (tail) {
    tail->next = newNode;
  } else {
    head = newNode;
  }
  tail = newNode;
  ++capacity;
}

template <typename T>
void S21Queue<T>::pop() {
  if (!empty()) {
    Node *temp = head;
    head = head->next;
    delete temp;
    --capacity;
    if (empty()) {
      tail = nullptr;
    }
  }
}

template <typename T>
void S21Queue<T>::swap(S21Queue &other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(capacity, other.capacity);
}

template <typename T>
template <typename... Args>
void S21Queue<T>::insert_many_back(Args &&...args) {
  T tempArray[] = {std::forward<Args>(args)...};
  size_type numElements = sizeof...(Args);

  for (size_type i = 0; i < numElements; ++i) {
    push(tempArray[i]);
  }
}

}  // namespace s21

#endif /* CPP2_S21_CONTAINERS_1_Queue_S21_Queue_H_ */