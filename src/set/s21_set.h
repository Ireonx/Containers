#ifndef CPP2_S21_CONTAINERS_2_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_2_SET_S21_SET_H_

#include "../binary_search_tree/binary_search_tree.h"
#include "../list/s21_list.h"

namespace s21 {

template <typename T>
class S21Set : public s21::BinarySearchTree<T> {
 public:
  using value_type = T;
  using BinaryTree = BinarySearchTree<T>;
  using iterator = typename BinaryTree::iterator;
  using const_iterator = typename BinaryTree::ConstIterator;
  using size_type = size_t;
  using node = typename BinaryTree::node;

  S21Set() noexcept
      : BinaryTree::BinarySearchTree() {
  }  // default constructor, creates empty set
  S21Set(std::initializer_list<value_type> const &items)
      : BinaryTree::BinarySearchTree(items) {
  }  // initializer list constructor, creates the set initizialized using
     // std::initializer_list
  S21Set(const S21Set &s)
      : BinaryTree::BinarySearchTree(s) {}  // copy constructor
  S21Set(S21Set &&s)
      : BinaryTree::BinarySearchTree(std::move(s)) {}  // move constructor
  std::pair<iterator, bool> insert(const value_type &value) {
    value_type t = value;
    if (!this->contains(value)) {
      return BinaryTree::insert(std::move(t));
    } else {
      return BinaryTree::insert(std::move(t), 0);
    }
  }
  void merge(S21Set &other);  // splices nodes from another container
  S21Set &operator=(S21Set &&s) noexcept {
    BinaryTree::operator=(std::move(s));
    return *this;
  }  // assignment operator overload for moving object
  S21Set &operator=(S21Set &s) {
    BinaryTree::operator=(s);
    return *this;
  }  // assignment operator overload for moving object
};

template <typename T>
void S21Set<T>::merge(S21Set &other) {
  S21List<value_type> to_erase;
  for (auto it = other.begin(); it != other.end(); it++) {
    if (this->insert(std::move(*it)).second) {
      // this->insert(std::move(*it), 1);
      to_erase.push_front(*it);
    }
  }
  for (auto it = to_erase.begin(); it != to_erase.end(); it++) {
    other.erase(*it);
  }
}
}  // namespace s21

#endif