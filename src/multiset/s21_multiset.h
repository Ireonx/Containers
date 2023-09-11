
#ifndef CPP2S_S21_CONTAINERS_2_MULTISET_S21_MULTISET_H_
#define CPP2S_S21_CONTAINERS_2_MULTISET_S21_MULTISET_H_
#include "../binary_search_tree/binary_search_tree.h"

namespace s21 {

template <typename T>
class S21Multiset : public BinarySearchTree<T> {
 public:
  using value_type = T;
  using BinaryTree = BinarySearchTree<T>;
  using iterator = typename BinaryTree::Iterator;
  using node = typename BinaryTree::node;
  using size_type = typename BinaryTree::size_type;
  using Key = value_type;
  S21Multiset()
      : BinaryTree::BinarySearchTree() {
  }  // default constructor, creates empty set
  S21Multiset(std::initializer_list<value_type> const
                  &items);  // initializer list constructor, creates the set
                            // initizialized using std::initializer_list
  S21Multiset(const S21Multiset &ms)
      : BinaryTree::BinarySearchTree(ms) {}  // copy constructor
  S21Multiset(node *root) { this->root_ = root; }
  S21Multiset(S21Multiset &&ms) noexcept
      : BinaryTree::BinarySearchTree(std::move(ms)) {}  // move constructor
  std::pair<typename BinarySearchTree<T>::Iterator, bool> insert(
      value_type &val, int insertion = 1) override;  // insertion override
  std::pair<typename BinarySearchTree<T>::Iterator, bool> insert(
      value_type &&val) {
    return insert(val);
  }
  std::pair<typename BinarySearchTree<T>::Iterator, bool> insert(
      node *val, int insertion = 1) override;  // insertion override
  S21Multiset &operator=(S21Multiset &another) {
    BinaryTree::operator=(another);
    return *this;
  }  // assignment copy operator
  S21Multiset &operator=(S21Multiset &&another) noexcept {
    BinaryTree::operator=(std::move(another));
    return *this;
  }  // assignment move operator
  size_type count(const Key &key)
      const noexcept;  // returns the number of elements matching specific key
  std::pair<iterator, iterator> equal_range(const Key &key)
      const noexcept;  // returns range of elements matching a specific key
  iterator lower_bound(
      const Key &key) const noexcept;  // returns an iterator to the first
                                       // element not less than the given key
  iterator upper_bound(
      const Key &key) const noexcept;  // returns an iterator to the first
                                       // element greater than the given key
  void merge(
      S21Multiset &another) noexcept;  // merges elements from another multiset

 private:
  std::pair<node *, int> define_place_for_new_node_(value_type val,
                                                    int insertion = 0) noexcept;
  std::pair<iterator, bool> insert_new_node_(node *new_node,
                                             int insertion) noexcept;
};

template <typename T>
void S21Multiset<T>::merge(S21Multiset &another) noexcept {
  for (auto it = another.begin(); it != another.end(); it++) {
    insert(*it);
  }
  another.clear();
}

template <typename T>
std::pair<typename BinarySearchTree<T>::Iterator, bool> S21Multiset<T>::insert(
    value_type &val, int insertion) {
  node *new_node = BinaryTree::construct_node_(val);
  return insert_new_node_(new_node, insertion);
}

template <typename T>
std::pair<typename BinarySearchTree<T>::Iterator, bool> S21Multiset<T>::insert(
    node *val, int insertion) {
  return insert_new_node_(val, insertion);
}

template <typename T>
S21Multiset<T>::S21Multiset(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); it++) {
    value_type to_insert = *it;
    insert(to_insert, 1);
  }
}

template <typename T>
std::pair<typename BinarySearchTree<T>::Iterator, bool>
S21Multiset<T>::insert_new_node_(node *new_node, int insertion) noexcept {
  if (this->root_ == nullptr) {
    this->root_ = new_node;
    iterator it(this->root_, 0);
    return std::make_pair(it, true);
  }
  auto place = define_place_for_new_node_(new_node->info, insertion);
  if (place.second == 1) {
    place.first->right = new_node;
    iterator it(this->root_, new_node,
                this->find_index_by_value_(new_node->info));
    return std::make_pair(it, true);
  }
  place.first->left = new_node;
  iterator it(this->root_, new_node,
              this->find_index_by_value_(new_node->info));
  return std::make_pair(it, true);
}

template <typename T>
std::pair<typename BinarySearchTree<T>::node *, int>
S21Multiset<T>::define_place_for_new_node_(value_type val,
                                           int insertion) noexcept {
  insertion = 1;
  node *current = this->root_;
  node *prev = nullptr;
  int side = 0;
  while (current) {
    if (val >= current->info) {
      current->right_descendents_amount += insertion;
      prev = current;
      current = current->right;
      side = right_side;
    } else {
      current->left_descendents_amount += insertion;
      prev = current;
      current = current->left;
      side = left_side;
    }
  }
  return std::make_pair(prev, side);
}

template <typename T>
typename S21Multiset<T>::size_type S21Multiset<T>::count(
    const Key &key) const noexcept {
  if (this->root_ == nullptr) {
    return 0;
  }
  auto it = this->find(key);
  size_type count = 0;
  while (it != this->end() && *it == key) {
    count++;
    *it++;
  }
  return count;
}

template <typename T>
std::pair<typename S21Multiset<T>::iterator, typename S21Multiset<T>::iterator>
S21Multiset<T>::equal_range(const Key &key) const noexcept {
  if (this->root_ == nullptr) {
    iterator it(this->root_);
    return std::make_pair(it, it);
  }
  auto start_of_range = this->find(key);
  auto end_of_range = start_of_range;
  while (*start_of_range == *end_of_range) {
    end_of_range++;
  }
  return std::make_pair(start_of_range, end_of_range);
}

template <typename T>
typename S21Multiset<T>::iterator S21Multiset<T>::lower_bound(
    const Key &key) const noexcept {
  if (this->root_ == nullptr) {
    iterator it(this->root_);
    return it;
  }
  node *cur = this->root_;
  while (cur->info < key) {
    cur = cur->right;
  }
  iterator it(this->root_, cur, this->find_index_by_value_(cur->info));
  return it;
}

template <typename T>
typename S21Multiset<T>::iterator S21Multiset<T>::upper_bound(
    const Key &key) const noexcept {
  if (this->root_ == nullptr) {
    iterator it(this->root_);
    return it;
  }
  node *cur = this->root_;
  while (!(cur->info > key)) {
    cur = cur->right;
  }
  iterator it(this->root_, cur, this->find_index_by_value_(cur->info));
  return it;
}
}  // namespace s21

#endif