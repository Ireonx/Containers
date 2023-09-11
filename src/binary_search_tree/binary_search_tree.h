#ifndef CPP2_S21_CONTAINERS_2_BINARY_SEARCH_TREE_BINARY_SEARCH_TREE_H_
#define CPP2_S21_CONTAINERS_2_BINARY_SEARCH_TREE_BINARY_SEARCH_TREE_H_

#include <cstddef>

#include "../list/s21_list.h"
#include "../stack/s21_stack.h"
// #include "../s21_containers.h"

namespace s21 {
constexpr int equal = 0;
constexpr int bigger = 1;
constexpr int smaller = -1;
constexpr int right_side = 1;
constexpr int left_side = -1;
template <typename T>

class BinarySearchTree {
  static constexpr long max_long = 9223372036854775807L;

 public:
  class ConstIterator;
  class Iterator;
  using value_type = T;
  using size_type = size_t;
  using iterator = BinarySearchTree<T>::Iterator;
  typedef struct node {
   public:
    value_type info;
    node *right = nullptr;
    node *left = nullptr;
    size_type left_descendents_amount = 0;
    size_type right_descendents_amount = 0;
  } node;
  BinarySearchTree() noexcept;
  BinarySearchTree(node *root,
                   int (*custom_compare)(value_type a, value_type b)) noexcept;
  BinarySearchTree(int (*custom_compare)(value_type a, value_type b)) noexcept;
  BinarySearchTree(const BinarySearchTree &another);
  BinarySearchTree(BinarySearchTree &&another) noexcept;
  BinarySearchTree(std::initializer_list<value_type> const &items);
  ~BinarySearchTree();
  BinarySearchTree &operator=(const BinarySearchTree &another);
  BinarySearchTree &operator=(BinarySearchTree &&another) noexcept;
  virtual std::pair<typename BinarySearchTree<T>::Iterator, bool> insert(
      value_type &val, int insertion = 1);
  virtual std::pair<typename BinarySearchTree<T>::Iterator, bool> insert(
      value_type val, int insertion = 1);
  virtual std::pair<typename BinarySearchTree<T>::Iterator, bool> insert(
      node *val, int insertion = 1);
  iterator find(const value_type &val) const noexcept;
  void merge(BinarySearchTree &other);
  bool empty() const noexcept;
  size_type max_size() const noexcept;
  size_type size() const noexcept;
  bool contains(value_type &val) const noexcept;
  bool contains(value_type val) const noexcept;
  void swap(BinarySearchTree &another) noexcept;
  class ConstIterator {
   public:
    ConstIterator(node *root) noexcept;
    ConstIterator(node *root, int index);
    ConstIterator(const ConstIterator &another) noexcept;
    ConstIterator(ConstIterator &&another) noexcept;
    ConstIterator(node *root, node *cur, long cur_index_) noexcept;
    ConstIterator &operator=(const ConstIterator &another) noexcept;
    ConstIterator &operator=(ConstIterator &&another) noexcept;
    bool operator==(const ConstIterator &another) const;
    bool operator!=(const ConstIterator &another) const;
    ConstIterator &operator++() noexcept;
    ConstIterator operator++(int) noexcept;
    ConstIterator &operator--() noexcept;
    ConstIterator operator--(int) noexcept;
    ConstIterator &operator-(int) noexcept;
    ConstIterator &operator+(int) noexcept;
    value_type *operator->() noexcept;
    value_type &operator*();
    friend void BinarySearchTree<T>::erase(value_type value);
    friend void BinarySearchTree<T>::erase(iterator to_delete);

   protected:
    node *find_node_by_index_(long index) noexcept;
    long cur_index_;
    node *cur_;
    node *root_;
  };

  class Iterator : public ConstIterator {
   public:
    Iterator(node *root, int index) : ConstIterator(root, index) {}
    Iterator(node *root, node *cur, long cur_index)
        : ConstIterator(root, cur, cur_index) {}
    Iterator(node *root) : ConstIterator(root) {}
    value_type *operator->();
    value_type &operator*();
  };

  void clear();
  void erase(value_type value);
  void erase(iterator to_delete);
  Iterator begin() const noexcept;
  Iterator end() const noexcept;

 protected:
  node *root_;
  int (*custom_compare_)(value_type a, value_type b) = nullptr;
  long find_index_by_value_(value_type &a) const noexcept;
  void insert_descendent_of_deleted_(value_type a);
  void info_cp(node *destination, node *source) const noexcept;
  node *find_node_by_value_(value_type &val) const noexcept;
  std::pair<typename BinarySearchTree<value_type>::Iterator, bool>
  insert_new_node_(node *new_node, int insertion = 0);
  std::pair<node *, int> define_place_for_new_node_(value_type val,
                                                    int insertion = 0);
  int compare_(value_type a, value_type b) const;
  node *construct_node_(value_type a) const noexcept {
    node *n = new node;
    n->info = a;
    n->left_descendents_amount = 0;
    n->right_descendents_amount = 0;
    n->left = nullptr;
    n->right = nullptr;
    return n;
  }
};

template <typename T>
void BinarySearchTree<T>::swap(BinarySearchTree &another) noexcept {
  node *tmp = root_;
  root_ = another.root_;
  another.root_ = tmp;
}

template <typename T>
typename BinarySearchTree<T>::iterator BinarySearchTree<T>::find(
    const value_type &val) const noexcept {
  value_type value = val;
  node *cur = find_node_by_value_(value);
  if (cur == nullptr) {
    Iterator it(root_);
    return it;
  } else {
    Iterator it(root_, cur, find_index_by_value_(cur->info));
    return it;
  }
}

template <typename T>
bool BinarySearchTree<T>::contains(value_type &val) const noexcept {
  if (find_node_by_value_(val) == nullptr) {
    return false;
  }
  return true;
}

template <typename T>
bool BinarySearchTree<T>::contains(value_type val) const noexcept {
  if (find_node_by_value_(val) == nullptr) {
    return false;
  }
  return true;
}

template <typename T>
void BinarySearchTree<T>::info_cp(node *destination,
                                  node *source) const noexcept {
  destination->info = source->info;
  destination->left_descendents_amount = source->left_descendents_amount;
  destination->right_descendents_amount = source->right_descendents_amount;
}

template <typename T>
void BinarySearchTree<T>::insert_descendent_of_deleted_(value_type a) {
  node *to_ins = construct_node_(a);
  insert_new_node_(to_ins);
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(
    node *root, int (*custom_compare)(value_type a, value_type b)) noexcept {
  root_ = root;
  custom_compare_ = custom_compare;
}

template <typename T>
int BinarySearchTree<T>::compare_(BinarySearchTree<T>::value_type a,
                                  BinarySearchTree<T>::value_type b) const {
  if (custom_compare_ == nullptr) {
    if (a > b) {
      return bigger;
    }
    if (a < b) {
      return smaller;
    }
    if (a == b) {
      return equal;
    }
  }
  return (*custom_compare_)(a, b);
}

template <typename T>
void BinarySearchTree<T>::merge(BinarySearchTree &other) {
  S21List<value_type> to_erase;
  for (auto it = other.begin(); it != other.end(); it++) {
    if (insert(std::move(*it)).second) {
      to_erase.push_front(*it);
    }
  }
  for (auto it = to_erase.begin(); it != to_erase.end(); it++) {
    other.erase(*it);
  }
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
  clear();
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree() noexcept {
  root_ = nullptr;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(
    int (*custom_compare)(value_type a, value_type b)) noexcept {
  root_ = nullptr;
  custom_compare_ = custom_compare;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree &&another) noexcept {
  root_ = another.root_;
  custom_compare_ = another.custom_compare_;
  another.root_ = nullptr;
  another.custom_compare_ = nullptr;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(
    std::initializer_list<value_type> const &items) {
  root_ = nullptr;
  for (auto it = items.begin(); it != items.end(); it++) {
    node *new_node = construct_node_(*it);
    insert_new_node_(new_node, 1);
  }
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree const &another) {
  root_ = nullptr;
  *this = another;
}

template <typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator=(
    BinarySearchTree const &another) {
  clear();
  if (another.root_ == nullptr) {
    root_ = nullptr;
    return *this;
  }
  S21Stack<node *> stack_another_tree;
  S21Stack<node *> stack_this_tree;
  stack_another_tree.push(nullptr);
  stack_this_tree.push(nullptr);
  node *current_another_tree = another.root_;
  node *current_cp = new node;
  root_ = current_cp;
  info_cp(current_cp, current_another_tree);
  do {
    if (current_another_tree != nullptr) {
      if (current_another_tree->right) {
        stack_another_tree.push(current_another_tree->right);
      }
      info_cp(current_cp, current_another_tree);
      if (current_another_tree->left) {
        node *cp_node_left = new node;
        info_cp(cp_node_left, current_another_tree->left);
        current_cp->left = cp_node_left;
      } else {
        current_cp->left = nullptr;
      }

      if (current_another_tree->right) {
        node *cp_node_right = new node;
        info_cp(cp_node_right, current_another_tree->right);
        current_cp->right = cp_node_right;
        stack_this_tree.push(current_cp->right);
      } else {
        current_cp->right = nullptr;
      }

      current_cp = current_cp->left;
      current_another_tree = current_another_tree->left;
    } else {
      current_another_tree = stack_another_tree.top();
      current_cp = stack_this_tree.top();
      stack_another_tree.pop();
      stack_this_tree.pop();
    }
  } while (!stack_another_tree.empty());
  return *this;
}

template <typename T>
bool BinarySearchTree<T>::empty() const noexcept {
  if (root_ == nullptr) {
    return true;
  }
  return false;
}

template <typename T>
typename BinarySearchTree<T>::size_type BinarySearchTree<T>::size()
    const noexcept {
  if (root_ == nullptr) {
    return 0;
  }
  return root_->left_descendents_amount + root_->right_descendents_amount + 1;
}

template <typename T>
typename BinarySearchTree<T>::size_type BinarySearchTree<T>::max_size()
    const noexcept {
  return max_long;
}

template <typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator=(
    BinarySearchTree &&another) noexcept {
  clear();
  root_ = another.root_;
  another.root_ = nullptr;
  return *this;
}

template <typename T>
void BinarySearchTree<T>::clear() {
  S21Stack<node *> st;
  st.push(root_);
  node *cur = root_;
  while (!st.empty()) {
    if (cur) {
      if (cur->right) {
        st.push(cur->right);
      }
      node *next = cur->left;
      delete cur;
      cur = next;
    } else {
      cur = st.top();
      st.pop();
    }
  }
  root_ = nullptr;
  custom_compare_ = nullptr;
}

template <typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::begin()
    const noexcept {
  Iterator it(root_, 0);
  return it;
}

template <typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::end()
    const noexcept {
  Iterator it(root_);
  return it;
}

template <typename T>
typename BinarySearchTree<T>::node *
BinarySearchTree<T>::ConstIterator::find_node_by_index_(long index) noexcept {
  if (index < 0 || index > (long)root_->left_descendents_amount +
                               (long)root_->right_descendents_amount) {
    cur_ = nullptr;
    cur_index_ = -1;
    return cur_;
  }
  index++;
  unsigned long cur_index = root_->left_descendents_amount + 1;
  unsigned long last_index_before_right = 0;
  node *cur = root_;
  while (index != (long)cur_index) {
    if ((long)cur_index > index) {
      cur = cur->left;
      cur_index = cur->left_descendents_amount + last_index_before_right + 1;
    }
    if ((long)cur_index < index) {
      last_index_before_right = cur_index;
      cur = cur->right;
      cur_index = last_index_before_right + cur->left_descendents_amount + 1;
    }
  }
  return cur;
}

template <typename T>
BinarySearchTree<T>::ConstIterator::ConstIterator(node *root) noexcept {
  root_ = root;
  cur_ = nullptr;
  cur_index_ = -1;
}

template <typename T>
BinarySearchTree<T>::ConstIterator::ConstIterator(node *root, int index) {
  root_ = root;
  if (root_ == nullptr) {
    cur_ = nullptr;
  } else {
    cur_ = find_node_by_index_(index);
  }
  cur_index_ = index;
}

template <typename T>
BinarySearchTree<T>::ConstIterator::ConstIterator(
    const ConstIterator &another) noexcept {
  root_ = another.root_;
  cur_ = another.cur_;
  cur_index_ = another.cur_index_;
}

template <typename T>
BinarySearchTree<T>::ConstIterator::ConstIterator(
    ConstIterator &&another) noexcept {
  root_ = another.root_;
  another.root_ = nullptr;
  cur_ = another.cur_;
  another.cur_ = nullptr;
  cur_index_ = another.cur_index_;
  another.cur_index_ = 0;
}

template <typename T>
BinarySearchTree<T>::ConstIterator::ConstIterator(node *root, node *cur,
                                                  long cur_index) noexcept {
  root_ = root;
  cur_ = cur;
  cur_index_ = cur_index;
}

template <typename T>
long BinarySearchTree<T>::find_index_by_value_(value_type &a) const noexcept {
  node *cur = root_;
  long cur_index = cur->left_descendents_amount + 1;
  long last_index_before_right = 0;
  int comp = 0;
  while ((comp = compare_(a, cur->info)) != 0) {
    if (comp == 1) {
      last_index_before_right = cur_index;
      cur = cur->right;
      cur_index += cur->left_descendents_amount + 1;
    } else {
      cur = cur->left;
      cur_index = cur->left_descendents_amount + 1 + last_index_before_right;
    }
  }
  if (cur) {
    return --cur_index;
  }
  return -1;
}

template <typename T>
typename BinarySearchTree<T>::ConstIterator &
BinarySearchTree<T>::ConstIterator::operator=(
    const ConstIterator &another) noexcept {
  cur_ = another.cur_;
  root_ = another.root_;
  cur_index_ = another.cur_index_;
  return *this;
}

template <typename T>
typename BinarySearchTree<T>::ConstIterator &
BinarySearchTree<T>::ConstIterator::operator=(
    ConstIterator &&another) noexcept {
  cur_ = another.cur_;
  root_ = another.root_;
  cur_index_ = another.cur_index_;
  another.cur_ = nullptr;
  another.root_ = nullptr;
  another.cur_index_ = -1;
  return *this;
}

template <typename T>
bool BinarySearchTree<T>::ConstIterator::operator==(
    const ConstIterator &another) const {
  if (root_ != another.root_) {
    return false;
  }
  if (cur_ != another.cur_) {
    return false;
  }
  if (cur_index_ != another.cur_index_) {
    return false;
  }
  return true;
}

template <typename T>
bool BinarySearchTree<T>::ConstIterator::operator!=(
    const ConstIterator &another) const {
  if (root_ == another.root_ && cur_ == another.cur_) {
    return false;
  }
  return true;
}

template <typename T>
typename BinarySearchTree<T>::ConstIterator &
BinarySearchTree<T>::ConstIterator::operator++() noexcept {
  cur_ = find_node_by_index_(++cur_index_);
  if (cur_ == nullptr) {
    cur_index_ = -1;
  }
  return *this;
}

template <typename T>
typename BinarySearchTree<T>::ConstIterator
BinarySearchTree<T>::ConstIterator::operator++(int) noexcept {
  ConstIterator it = *this;
  ++(*this);
  return it;
}

template <typename T>
typename BinarySearchTree<T>::ConstIterator &
BinarySearchTree<T>::ConstIterator::operator--() noexcept {
  cur_ = find_node_by_index_(--cur_index_);
  if (cur_ == nullptr) {
    cur_index_ = -1;
  }
  return *this;
}

template <typename T>
typename BinarySearchTree<T>::ConstIterator
BinarySearchTree<T>::ConstIterator::operator--(int) noexcept {
  ConstIterator it = *this;
  --(*this);
  return it;
}

template <typename T>
typename BinarySearchTree<T>::ConstIterator &
BinarySearchTree<T>::ConstIterator::operator-(int n) noexcept {
  cur_index_ -= n;
  cur_ = find_node_by_index_(cur_index_);
  return *this;
}

template <typename T>
typename BinarySearchTree<T>::ConstIterator &
BinarySearchTree<T>::ConstIterator::operator+(int n) noexcept {
  cur_index_ += n;
  cur_ = find_node_by_index_(cur_index_);
  return *this;
}

template <typename T>
typename BinarySearchTree<T>::value_type *
BinarySearchTree<T>::ConstIterator::operator->() noexcept {
  if (cur_ == nullptr) {
    return nullptr;
  }
  const value_type *ptr = &(cur_->info);
  return ptr;
}

template <typename T>
typename BinarySearchTree<T>::value_type &
BinarySearchTree<T>::ConstIterator::operator*() {
  if (cur_ == nullptr) {
    throw std::out_of_range("Tried to dereference pointer to null");
  }
  return cur_->info;
}

template <typename T>
typename BinarySearchTree<T>::value_type *
BinarySearchTree<T>::Iterator::operator->() {
  return &(this->cur_->info);
}

template <typename T>
typename BinarySearchTree<T>::value_type &
BinarySearchTree<T>::Iterator::operator*() {
  return this->cur_->info;
}

template <typename T>
typename BinarySearchTree<T>::node *BinarySearchTree<T>::find_node_by_value_(
    typename BinarySearchTree<T>::value_type &val) const noexcept {
  if (root_ == nullptr) {
    return nullptr;
  }
  node *cur = root_;
  while (int comp = compare_(cur->info, val) != 0) {
    if (comp == 1) {
      cur = cur->right;
    } else if (comp == -1) {
      cur = cur->left;
    }
    if (cur == nullptr) {
      break;
    }
  }
  return cur;
}

template <typename T>
void BinarySearchTree<T>::erase(value_type value) {
  bool deleting_root = false;
  BinarySearchTree<T> descendets_of_deleted(find_node_by_value_(value),
                                            custom_compare_);
  std::pair<node *, int> parent_of_erased = define_place_for_new_node_(value);
  if (parent_of_erased.first == nullptr) {
    deleting_root = true;
  }
  node *cur = root_;
  int comp = 0;
  if (!deleting_root) {
    while ((comp = compare_(value, cur->info)) != 0) {
      if (comp == 1) {
        cur->right_descendents_amount--;
        cur = cur->right;
      } else if (comp == -1) {
        cur->left_descendents_amount--;
        cur = cur->left;
      }
    }
    if (parent_of_erased.second == -1) {
      parent_of_erased.first->left = nullptr;
    } else if (parent_of_erased.second == 1) {
      parent_of_erased.first->right = nullptr;
    }
  } else {
    root_ = nullptr;
  }
  for (auto it = descendets_of_deleted.begin();
       it != descendets_of_deleted.end(); it++) {
    if (it.cur_ == descendets_of_deleted.root_) {
      continue;
    }
    if (deleting_root) {
      insert(construct_node_(it.cur_->info), 1);
    } else {
      insert_descendent_of_deleted_(*it);
    }
  }
}

template <typename T>
void BinarySearchTree<T>::erase(iterator to_delete) {
  erase(*to_delete);
}

template <typename T>
std::pair<typename BinarySearchTree<T>::Iterator, bool>
BinarySearchTree<T>::insert(value_type &val, int insertion) {
  node *new_node = construct_node_(val);
  return insert_new_node_(new_node, insertion);
}

template <typename T>
std::pair<typename BinarySearchTree<T>::Iterator, bool>
BinarySearchTree<T>::insert(value_type val, int insertion) {
  node *new_node = construct_node_(val);
  return insert_new_node_(new_node, insertion);
}

template <typename T>
std::pair<typename BinarySearchTree<T>::Iterator, bool>
BinarySearchTree<T>::insert(node *val, int insertion) {
  return insert_new_node_(val, insertion);
}

template <typename T>
std::pair<typename BinarySearchTree<T>::Iterator, bool>
BinarySearchTree<T>::insert_new_node_(node *new_node, int insertion) {
  if (root_ == nullptr) {
    root_ = new_node;
    Iterator it(root_, 0);
    return std::make_pair(it, true);
  }
  std::pair<node *, int> place =
      define_place_for_new_node_(new_node->info, insertion);
  if (place.second == 1 && !place.first->right) {
    place.first->right = new_node;
    Iterator it(root_, new_node, find_index_by_value_(new_node->info));
    return std::make_pair(it, true);
  }
  if (place.second == -1 && !place.first->left) {
    place.first->left = new_node;
    Iterator it(root_, new_node, find_index_by_value_(new_node->info));
    return std::make_pair(it, true);
  }
  Iterator it(root_, place.first, find_index_by_value_(new_node->info));
  delete new_node;
  return std::make_pair(it, false);
}

template <typename T>
std::pair<typename BinarySearchTree<T>::node *, int>
BinarySearchTree<T>::define_place_for_new_node_(value_type val, int insertion) {
  node *current = root_;
  node *prev = nullptr;
  int side = 0;
  int comp = 0;
  while (current && (comp = compare_(current->info, val)) != 0) {
    if (comp == -1) {
      current->right_descendents_amount += insertion;
      prev = current;
      current = current->right;
      side = right_side;
    } else if (comp == 1) {
      current->left_descendents_amount += insertion;
      prev = current;
      current = current->left;
      side = left_side;
    }
  }
  return std::make_pair(prev, side);
}

}  // namespace s21
#endif