#ifndef CPP2_S21_CONTAINERS_2_LIST_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_2_LIST_S21_VECTOR_H_
#include <stddef.h>

#include <iostream>
#include <limits>
namespace s21 {

template <typename T>
class S21Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  S21Vector()
      : m_size(0), m_capacity(0), arr(nullptr) {}  // default constructor

  explicit S21Vector(size_type n)
      : m_size(n),
        m_capacity(n),
        arr(n ? new value_type[n]() : nullptr) {}  // parametrized constructor

  S21Vector(std::initializer_list<value_type> const &items) : S21Vector() {
    m_capacity = items.size();
    reserve(m_capacity);
    for (auto obj : items) {
      arr[m_size++] = obj;
    }
  };  // initializer list constructor

  S21Vector(const S21Vector &v) : m_size(v.m_size), m_capacity(v.m_capacity) {
    arr = new value_type[v.m_capacity];
    std::copy(v.arr, v.arr + v.m_capacity, arr);
  };
  // copy constructor

  S21Vector(S21Vector &&v)
      : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {
    v.arr = nullptr;
    v.m_size = 0;
    v.m_capacity = 0;
  }  // move constructor

  S21Vector &operator=(S21Vector &&v) noexcept {
    if (this != &v) {
      delete[] arr;
      m_size = 0;
      m_capacity = 0;
      arr = nullptr;
      std::swap(m_size, v.m_size);
      std::swap(m_capacity, v.m_capacity);
      std::swap(arr, v.arr);
    }
    return *this;
  };  // assignment operator overload for moving an object

  S21Vector &operator=(const S21Vector &v) {
    m_size = v.m_size;
    m_capacity = v.m_capacity;
    arr = new value_type[v.m_capacity];
    std::copy(v.arr, v.arr + v.m_capacity, arr);
    return *this;
  };  // assignment operator overload for copying an object
  // destructor

  ~S21Vector() {
    delete[] arr;
    arr = nullptr;
  }

  // S21Vector Element access

  reference at(const size_type pos) const {
    if (pos >= m_capacity) {
      throw std::out_of_range("Position is out of bounds");
    } else {
      return arr[pos];
    }
  }  // access a specified element with bounds checking

  reference operator[](const size_type pos) const noexcept {
    return at(pos);
  };  // access a specified element

  const_reference front() const { return at(0); };  // access the first element

  const_reference back() const {
    return at(m_size - 1);
  };  // access the last element

  iterator data() const noexcept {
    return arr;
  };  // direct access the underlying array

  // S21Vector Iterators

  iterator begin() const noexcept {
    return iterator(arr);
  };  // returns an iterator to the beginning
  iterator end() const noexcept {
    return iterator(arr + size());
  };  // returns an iterator to the end
  // S21Vector Capacity

  bool empty() const noexcept {
    return (m_size == 0);
  };  // checks whether the container is empty
  size_type size() const noexcept {
    return m_size;
  };  // returns the number of elements
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }  // returns the maximum possible number of elements
  void reserve(const size_type size) {
    if (size > m_size) {
      iterator temp = new T[size];
      std::move(arr, arr + m_size, temp);
      delete[] arr;
      arr = temp;
      m_capacity = size;
    }
  };  // allocate storage of size elements and copies current
      // array elements to a newely allocated array
  size_type capacity() const noexcept {
    return m_capacity;
  };  // returns the number of elements that can be held in
      // currently allocated storage
  void shrink_to_fit() noexcept {
    if (m_size < m_capacity) {
      iterator temp = new T[m_size];
      std::move(arr, arr + m_size, temp);
      delete[] arr;
      arr = temp;
      m_capacity = m_size;
    }
  };  // reduces memory usage by freeing unused memory
      // S21Vector Modifiers
  void clear() noexcept {
    delete[] arr;
    arr = nullptr;
    m_size = 0;
  };  // clears the contents
  iterator insert(iterator pos, const_reference value) noexcept {
    size_type diff = pos - begin();
    push_back(value);
    for (size_type i = m_size - 1; i > diff; --i) {
      std::swap(arr[i], arr[i - 1]);
    }
    return pos;
  };  // inserts element into concrete pos and returns
      // the iterator that points to the new element
  template <typename... Args>
  iterator insert_many(const_iterator pos,
                       Args &&...args);   // inserts new elements into the
  template <typename... Args>             // container directly before pos
  void insert_many_back(Args &&...args);  // appends new elements to the
                                          // end of the container
  void erase(iterator pos) {
    std::move(pos + 1, end(), pos);
    --m_size;
  };  // erases an element at pos
  void push_back(const_reference value) noexcept {
    if (m_size == m_capacity) {
      reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    arr[m_size++] = value;
  };  // adds an element to the end
  void pop_back() noexcept {
    if (m_size) {
      --m_size;
    }
  };  // removes the last element
  void swap(S21Vector &other) noexcept {
    std::swap(arr, other.arr);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  };  // swaps the contents

  void print() {
    for (size_type i = 0; i < m_size; ++i) {
      std::cout << at(i) << " ";
    }
    std::cout << std::endl;
  }

 private:
  size_type m_size;
  size_type m_capacity;
  iterator arr;
};
template <typename T>
template <typename... Args>
typename S21Vector<T>::iterator S21Vector<T>::insert_many(const_iterator pos,
                                                          Args &&...args) {
  size_type first_index = pos - begin();
  iterator insertion_point = begin() + first_index;
  ((insert(++insertion_point, std::forward<Args>(args))), ...);
  return const_cast<iterator>(pos);
}
template <typename T>
template <typename... Args>
void S21Vector<T>::insert_many_back(Args &&...args) {
  ((push_back(std::forward<Args>(args))), ...);
}
}  // namespace s21
#endif /* CPP2_S21_CONTAINERS_1_LIST_S21_VECTOR_H_*/
