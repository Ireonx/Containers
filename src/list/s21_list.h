#ifndef CPP2_S21_CONTAINERS_2_S21List_S21_S21List_H_
#define CPP2_S21_CONTAINERS_2_S21List_S21_S21List_H_
#include <initializer_list>
#include <utility>

namespace s21 {
template <typename T>
class S21List {
  struct Node;

 public:
  class S21ListConstIterator;
  class S21ListIterator;
  using pointer = T *;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = S21ListIterator;
  using const_iterator = S21ListConstIterator;

  S21List();
  S21List(size_type n);
  S21List(std::initializer_list<value_type> const &items);
  S21List(const S21List &l) : head(nullptr), tail(nullptr), capacity(0) {
    for (const auto &item : l) {
      push_back(item);
    }
  }
  S21List(S21List &&l);
  ~S21List();
  S21List<T> &operator=(const S21List<T> &other) noexcept;
  S21List<T> &operator=(S21List<T> &&other) noexcept;

  const_reference front() const { return (head) ? head->data : value_type{}; }
  const_reference back() const { return (tail) ? tail->data : value_type{}; }

  iterator begin() { return S21ListIterator(head); }
  iterator end() { return S21ListIterator(); }

  const_iterator begin() const { return S21ListConstIterator(head); }
  const_iterator end() const { return S21ListConstIterator(); }

  bool empty() const { return (capacity == 0); }
  size_type size() const { return capacity; }

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);  // erases an element at pos
  void push_back(const_reference value);
  void pop_back();                         // removes the last element
  void push_front(const_reference value);  // adds an element to the head
  void pop_front();                        // removes the first element
  void swap(S21List &other);               // swaps the contents
  void merge(S21List &other);              // merges two sorted S21Lists
  void splice(const_iterator pos,
              S21List &other);  // transfers elements from S21List other
                                // starting from pos
  void reverse();               // reverses the order of the elements
  void unique();                // removes consecutive duplicate elements
  void sort();                  // sorts the elements

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);

  class S21ListConstIterator {
   public:
    S21ListConstIterator() noexcept : ptr_(nullptr) {}
    explicit S21ListConstIterator(Node *node) noexcept : ptr_(node) {}
    S21ListConstIterator(const S21ListConstIterator &other) noexcept
        : ptr_(other.ptr_) {}
    ~S21ListConstIterator() = default;

    bool operator!=(const S21ListConstIterator &other) const noexcept {
      return ptr_ != other.ptr_;
    }

    bool operator==(const S21ListConstIterator &other) const noexcept {
      return ptr_ == other.ptr_;
    }

    S21ListConstIterator &operator=(
        const S21ListConstIterator &other) noexcept {
      if (this != &other) ptr_ = other.ptr_;
      return *this;
    }

    const_reference operator*() const noexcept { return ptr_->data; }

    S21ListConstIterator operator++(int) noexcept {
      S21ListConstIterator tmp(*this);
      Operation_(true);
      return tmp;
    }

    S21ListConstIterator &operator++() noexcept {
      Operation_(true);
      return *this;
    }

    S21ListConstIterator operator--(int) noexcept {
      S21ListConstIterator tmp(*this);
      Operation_(false);
      return tmp;
    }

    S21ListConstIterator &operator--() noexcept {
      Operation_(false);
      return *this;
    }

    S21ListConstIterator operator+(size_type n) noexcept {
      auto it_tmp = *this;
      while (n-- > 0) it_tmp.Operation_(true);
      return it_tmp;
    }

    S21ListConstIterator operator-(size_type n) noexcept {
      auto it_tmp = *this;
      while (n-- > 0) it_tmp.Operation_(false);
      return it_tmp;
    }

    S21ListConstIterator &operator+=(size_type n) noexcept {
      while (n-- > 0) Operation_(true);
      return *this;
    }

    S21ListConstIterator &operator-=(size_type n) noexcept {
      while (n-- > 0) Operation_(false);
      return *this;
    }

    Node *GetNode_() const noexcept { return ptr_; }
    S21List &GetList_() const noexcept { return *owner_list; }

   protected:
    Node *ptr_;
    S21List *owner_list;
    void Operation_(bool isPlus) noexcept {
      if (isPlus)
        ptr_ = ptr_->next;
      else
        ptr_ = ptr_->prev;
    }
  };

  class S21ListIterator : public S21ListConstIterator {
   public:
    S21ListIterator() noexcept : S21ListConstIterator() {}
    explicit S21ListIterator(Node *node) noexcept
        : S21ListConstIterator(node) {}
    S21ListIterator(const S21ListIterator &other) noexcept
        : S21ListConstIterator(other) {}
    ~S21ListIterator() = default;

    S21ListIterator &operator=(const S21ListIterator &other) noexcept {
      if (this != &other) this->ptr_ = other.ptr_;
      return *this;
    }

    reference operator*() noexcept { return (reference)this->ptr_->data; }
  };

 private:
  struct Node {
    T data;
    Node *next;
    Node *prev;
  };

  Node *head;
  Node *tail;
  size_t capacity;
};

template <typename T>
S21List<T>::S21List() : head(nullptr), tail(nullptr), capacity(0) {}

template <typename T>
S21List<T>::S21List(S21List &&l)
    : head(l.head), tail(l.tail), capacity(l.capacity) {
  l.head = nullptr;
  l.tail = nullptr;
  l.capacity = 0;
}

template <typename T>
void S21List<T>::push_back(const_reference value) {
  Node *new_node = new Node;
  new_node->data = value;
  new_node->next = nullptr;
  new_node->prev = tail;
  if (tail) {
    tail->next = new_node;
  }
  tail = new_node;
  if (!head) {
    head = new_node;
  }
  ++capacity;
}

template <typename T>
S21List<T>::S21List(size_type n) : head(nullptr), tail(nullptr), capacity(0) {
  for (size_type i = 0; i < n; i++) {
    push_back(value_type{});
  }
}

template <typename T>
S21List<T>::S21List(std::initializer_list<value_type> const &items)
    : head(nullptr), tail(nullptr), capacity(0) {
  for (const auto &item : items) {
    push_back(item);
  }
}

template <typename T>
S21List<T> &S21List<T>::operator=(const S21List<T> &other) noexcept {
  if (this == &other) return *this;

  clear();

  for (const auto &item : other) {
    push_back(item);
  }

  return *this;
}

template <typename T>
S21List<T> &S21List<T>::operator=(S21List<T> &&other) noexcept {
  if (this == &other) return *this;

  clear();

  head = other.head;
  tail = other.tail;
  capacity = other.capacity;

  other.head = nullptr;
  other.tail = nullptr;
  other.capacity = 0;

  return *this;
}

template <typename T>
S21List<T>::~S21List() {
  clear();
}

template <typename T>
void S21List<T>::clear() {
  Node *current = head;
  while (current != nullptr) {
    Node *next_node = current->next;
    delete current;
    current = next_node;
  }

  head = nullptr;
  tail = nullptr;

  capacity = 0;
}

template <typename T>
void S21List<T>::reverse() {
  Node *current = head;
  Node *temp = nullptr;

  while (current != nullptr) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }

  if (temp != nullptr) {
    head = temp->prev;
  }
}

template <typename T>
typename S21List<T>::iterator S21List<T>::insert(iterator pos,
                                                 const_reference value) {
  Node *pos_node = pos.GetNode_();
  if (!pos_node) {
    push_back(value);
    return iterator(tail);
  }

  Node *new_node = new Node;
  new_node->data = value;
  new_node->next = pos_node;
  new_node->prev = pos_node->prev;

  if (pos_node->prev) {
    pos_node->prev->next = new_node;
  } else {
    head = new_node;
  }

  pos_node->prev = new_node;
  ++capacity;
  return iterator(new_node);
}

template <typename T>
void S21List<T>::erase(iterator pos) {
  Node *pos_node = pos.GetNode_();
  if (!pos_node) return;

  if (pos_node->prev)
    pos_node->prev->next = pos_node->next;
  else
    head = pos_node->next;

  if (pos_node->next)
    pos_node->next->prev = pos_node->prev;
  else
    tail = pos_node->prev;

  delete pos_node;
  --capacity;
}

template <typename T>
void S21List<T>::pop_back() {
  if (tail) {
    Node *prev_tail = tail->prev;
    if (prev_tail)
      prev_tail->next = nullptr;
    else
      head = nullptr;
    delete tail;
    tail = prev_tail;
    --capacity;
  }
}

template <typename T>
void S21List<T>::push_front(const_reference value) {
  Node *new_node = new Node;
  new_node->data = value;
  new_node->next = head;
  new_node->prev = nullptr;

  if (head) head->prev = new_node;

  head = new_node;
  if (!tail) tail = new_node;

  ++capacity;
}

template <typename T>
void S21List<T>::pop_front() {
  if (head) {
    Node *next_head = head->next;
    if (next_head)
      next_head->prev = nullptr;
    else
      tail = nullptr;
    delete head;
    head = next_head;
    --capacity;
  }
}

template <typename T>
void S21List<T>::swap(S21List &other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(capacity, other.capacity);
}

template <typename T>
void S21List<T>::merge(S21List &other) {
  if (this == &other) {
    return;
  }

  if (empty()) {
    head = other.head;
    tail = other.tail;
    capacity = other.capacity;

    other.head = nullptr;
    other.tail = nullptr;
    other.capacity = 0;
    return;
  }

  if (other.empty()) {
    return;
  }

  // Merge two sorted lists
  S21List merged_list;
  Node *current_this = head;
  Node *current_other = other.head;

  while (current_this && current_other) {
    if (current_this->data <= current_other->data) {
      merged_list.push_back(current_this->data);
      current_this = current_this->next;
    } else {
      merged_list.push_back(current_other->data);
      current_other = current_other->next;
    }
  }

  // Add remaining elements (if any) from both lists
  while (current_this) {
    merged_list.push_back(current_this->data);
    current_this = current_this->next;
  }

  while (current_other) {
    merged_list.push_back(current_other->data);
    current_other = current_other->next;
  }

  // Update the current list with the merged and sorted list
  swap(merged_list);
}

template <typename T>
void S21List<T>::splice(const_iterator pos, S21List<T> &other) {
  Node *pos_node = pos.GetNode_();
  if (!pos_node || &other == this) return;

  // Обработка пустого списка other
  if (other.head == nullptr) return;

  // Обновляем размер
  capacity += other.capacity;

  // Обновляем указатели
  if (pos_node->prev)
    pos_node->prev->next = other.head;
  else
    head = other.head;

  other.head->prev = pos_node->prev;
  other.tail->next = pos_node;

  pos_node->prev = other.tail;
  other.head = nullptr;
  other.tail = nullptr;
  other.capacity = 0;
}

template <typename T>
void S21List<T>::unique() {
  Node *current = head;
  while (current && current->next) {
    if (current->data == current->next->data) {
      Node *next_node = current->next->next;
      erase(iterator(current->next));
      current->next = next_node;
      if (next_node) next_node->prev = current;
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void S21List<T>::sort() {
  if (capacity <= 1) return;

  bool swapped;
  Node *ptr1;
  Node *lptr = nullptr;

  do {
    swapped = false;
    ptr1 = head;

    while (ptr1->next != lptr) {
      if (ptr1->data > ptr1->next->data) {
        std::swap(ptr1->data, ptr1->next->data);
        swapped = true;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}

template <typename T>
template <typename... Args>
typename S21List<T>::iterator S21List<T>::insert_many(const_iterator pos,
                                                      Args &&...args) {
  Node *pos_node = pos.GetNode_();
  if (!pos_node) {
    (push_back(std::forward<Args>(args)), ...);
    return iterator(tail);
  }

  for (const auto &arg : {std::forward<Args>(args)...}) {
    Node *new_node = new Node;
    new_node->data = arg;
    new_node->next = pos_node;
    new_node->prev = pos_node->prev;

    if (pos_node->prev)
      pos_node->prev->next = new_node;
    else
      head = new_node;

    pos_node->prev = new_node;
    ++capacity;

    pos_node = new_node;
  }

  return iterator(pos_node);
}

template <typename T>
template <typename... Args>
void S21List<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {std::forward<Args>(args)...}) {
    Node *new_node = new Node;
    new_node->data = arg;
    new_node->next = nullptr;
    new_node->prev = tail;

    if (tail) {
      tail->next = new_node;
    }
    tail = new_node;
    if (!head) {
      head = new_node;
    }
    ++capacity;
  }
}

template <typename T>
template <typename... Args>
void S21List<T>::insert_many_front(Args &&...args) {
  Node *current_head = head;

  for (const auto &arg : {std::forward<Args>(args)...}) {
    Node *new_node = new Node;
    new_node->data = arg;
    new_node->next = current_head;
    new_node->prev = nullptr;

    if (current_head) current_head->prev = new_node;

    current_head = new_node;
    if (!tail) tail = new_node;

    ++capacity;
  }

  head = current_head;
}

}  // namespace s21

#endif /* CPP2_S21_CONTAINERS_1_S21List_S21_S21List_H_ */
