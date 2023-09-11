#ifndef CPP2_S21_CONTAINERS_2_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_2_ARRAY_S21_ARRAY_H_
#include <stddef.h>

#include <iostream>
#include <limits>
namespace s21 {

template <typename T, size_t Size>
class S21Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  S21Array() : m_size(0), arr(nullptr) {}  // default constructor

  explicit S21Array(size_type n)
      : m_size(n),
        arr(n ? new value_type[n]() : nullptr) {}  // parametrized constructor

  S21Array(std::initializer_list<value_type> const &items) : S21Array() {
    m_size = items.size();
    int i = 0;
    arr = new value_type[m_size];
    for (auto obj : items) {
      arr[i++] = obj;
    }
  };  // initializer list constructor

  S21Array(const S21Array &v) : m_size(v.m_size) {
    arr = new value_type[v.m_size];
    std::copy(v.arr, v.arr + v.m_size, arr);
  };
  // copy constructor

  S21Array(S21Array &&v) : m_size(v.m_size), arr(v.arr) {
    v.arr = nullptr;
  }  // move constructor

  S21Array &operator=(S21Array &&v) noexcept {
    if (this != &v) {
      delete[] arr;
      m_size = 0;
      arr = nullptr;
      std::swap(m_size, v.m_size);
      std::swap(arr, v.arr);
    }
    return *this;
  };  // assignment operator overload for moving an object

  S21Array &operator=(const S21Array &v) {
    m_size = v.m_size;
    arr = new value_type[v.m_size];
    std::copy(v.arr, v.arr + v.m_size, arr);
    return *this;
  };  // assignment operator overload for copying an object
  // destructor

  ~S21Array() {
    delete[] arr;
    arr = nullptr;
  }

  // Vector Element access

  reference at(size_type pos) const {
    if (pos >= m_size) {
      throw std::out_of_range("Position is out of bounds");
    }
    return arr[pos];
  }  // access a specified element with bounds checking

  reference operator[](size_type pos) const {
    return at(pos);
  };  // access a specified element

  const_reference front() const { return at(0); };  // access the first element

  const_reference back() const {
    return at(m_size - 1);
  };  // access the last element

  iterator data() const {
    return arr;
  };  // direct access the underlying S21Array

  // Vector Iterators

  iterator begin() const noexcept {
    return iterator(arr);
  };  // returns an iterator to the beginning
  iterator end() const noexcept {
    return iterator(arr + size());
  };  // returns an iterator to the end
  // Array Capacity

  bool empty() const noexcept {
    return (m_size == 0);
  };  // checks whether the container is empty
  size_type size() const noexcept {
    return m_size;
  };  // returns the number of elements
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }  // returns the maximum possible number of elements

  // Array Modifiers

  void swap(S21Array &other) noexcept {
    std::swap(arr, other.arr);
    std::swap(m_size, other.m_size);
  };  // swaps the contents

  void fill(const_reference value) noexcept {
    for (size_type i = 0; i < m_size; ++i) {
      arr[i] = value;
    }
  };  // assigns the given value to all elements in the container
  void print() {
    for (size_type i = 0; i < m_size; ++i) {
      std::cout << at(i) << " ";
    }
    std::cout << std::endl;
  }

 private:
  size_type m_size;
  iterator arr;
};

}  // namespace s21
#endif /* CPP2_S21_CONTAINERS_1_ARRAY_S21_ARRAY_H_*/
