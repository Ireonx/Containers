#ifndef CPP2_S21_CONTAINERS_2_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_2_MAP_S21_MAP_H_

#include "../binary_search_tree/binary_search_tree.h"
#include "../list/s21_list.h"

namespace s21 {

template <typename Key, typename T>
class S21Map : public s21::BinarySearchTree<std::pair<Key, T>> {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = std::pair<const key_type, mapped_type> &;
  using const_reference = const reference;
  using BinaryTree = BinarySearchTree<value_type>;
  using iterator = typename BinaryTree::Iterator;
  using const_iterator = typename BinaryTree::ConstIterator;
  using size_type = size_t;
  using node = typename BinarySearchTree<value_type>::node;

 public:
  S21Map() noexcept
      : BinaryTree::BinarySearchTree(compare_) {
  }  // default constructor, creates an empty map
  S21Map(std::initializer_list<value_type> const &items) {
    BinaryTree::custom_compare_ = compare_;
    for (auto it = items.begin(); it != items.end(); it++) {
      insert(*it);
    }
  };  // initializer list constructor, creates the map
      // initizialized using std::initializer_list
  S21Map(const S21Map &m)
      : BinaryTree::BinarySearchTree(m) {}  // copy constructor
  S21Map(S21Map &&m) noexcept
      : BinaryTree::BinarySearchTree(std::move(m)) {}  // move constructor

  S21Map<Key, T> &operator=(
      const S21Map &m);  // assignment operator overload for copying an object
  S21Map &operator=(S21Map &&m) noexcept;  // assignment operator overload for
                                           // moving an object
  T &at(const Key &key);  // access a specified element with bounds checking
  T &operator[](const Key &key);  // access or insert specified element

  std::pair<iterator, bool> insert(
      const value_type
          &value);  // inserts a node and returns an iterator to where the
                    // element is in the container and bool denoting whether
                    // the insertion took place
  std::pair<iterator, bool> insert(
      const Key &key,
      const T &obj);  // inserts a value by key and returns an iterator to
                      // where the element is in the container and bool
                      // denoting whether the insertion took place
  std::pair<iterator, bool> insert_or_assign(
      const Key &key,
      const T &obj);         // inserts an element or assigns to the
                             // current element if the key already exists
  void erase(iterator pos);  // erases an element at pos
  void swap(S21Map &other) noexcept;  // swaps the contents
  void merge(S21Map &other);          // splices nodes from another container
  bool contains(
      const Key &key) const noexcept;  // checks if there is an element with key
                                       // equivalent to key in the container
  // S21Vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  static int compare_(value_type a, value_type b);

  node *find_node_by_key_(const Key &key) const noexcept;
};

template <typename Key, typename T>
std::pair<typename S21Map<Key, T>::iterator, bool> S21Map<Key, T>::insert(
    const value_type &value) {
  if (!contains(value.first)) {
    return BinaryTree::insert(value);
  } else {
    return BinaryTree::insert(value, 0);
  }
}

template <typename Key, typename T>
std::pair<typename S21Map<Key, T>::iterator, bool> S21Map<Key, T>::insert(
    const Key &key, const T &obj) {
  if (!contains(key)) {
    return BinaryTree::insert(std::make_pair(key, obj));
  } else {
    value_type val = std::make_pair(key, obj);
    iterator it(this->root_, this->find_node_by_value_(val),
                this->find_index_by_value_(val));
    return std::make_pair(it, false);
  }
}

template <typename Key, typename T>
std::pair<typename S21Map<Key, T>::iterator, bool>
S21Map<Key, T>::insert_or_assign(const Key &key, const T &obj) {
  if (contains(key)) {
    node *n = find_node_by_key_(key);
    iterator it(this->root_, n, this->find_index_by_value_(n->info));
    it->second = obj;
    return std::make_pair(it, false);
  }
  return insert(key, obj);
}

template <typename Key, typename T>
void S21Map<Key, T>::erase(iterator pos) {
  BinaryTree::erase(pos);
}

template <typename Key, typename T>
void S21Map<Key, T>::swap(S21Map &other) noexcept {
  node *tmp = BinaryTree::root_;
  BinaryTree::root_ = other.root_;
  other.root_ = tmp;
}

template <typename Key, typename T>
void S21Map<Key, T>::merge(S21Map &other) {
  S21List<value_type> to_erase;
  for (auto it = other.begin(); it != other.end(); it++) {
    if (insert(*it).second) {
      to_erase.push_front(*it);
    }
  }
  for (auto it = to_erase.begin(); it != to_erase.end(); it++) {
    other.BinaryTree::erase(*it);
  }
}

template <typename Key, typename T>
bool S21Map<Key, T>::contains(const Key &key) const noexcept {
  if (find_node_by_key_(key)) {
    return true;
  }
  return false;
}

template <typename Key, typename T>
typename S21Map<Key, T>::node *S21Map<Key, T>::find_node_by_key_(
    const Key &key) const noexcept {
  node *cur = BinaryTree::root_;
  while (cur && cur->info.first != key) {
    if (cur->info.first > key) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return cur;
}

template <typename Key, typename T>
T &S21Map<Key, T>::operator[](const Key &key) {
  if (!contains(key)) {
    mapped_type *a = new mapped_type;
    auto &res = insert_or_assign(key, *a).first->second;
    delete a;
    return res;
  } else {
    return at(key);
  }
}

template <typename Key, typename T>
T &S21Map<Key, T>::at(const Key &key) {
  node *a = find_node_by_key_(key);
  if (a == nullptr) {
    throw std::out_of_range("no such key in tree");
  }
  return a->info.second;
}

template <typename Key, typename T>
S21Map<Key, T> &S21Map<Key, T>::operator=(const S21Map &m) {
  BinaryTree::operator=(m);
  return *this;
}

template <typename Key, typename T>
S21Map<Key, T> &S21Map<Key, T>::operator=(S21Map &&m) noexcept {
  BinaryTree::operator=(m);
  return *this;
}

template <typename Key, typename T>
int S21Map<Key, T>::compare_(typename S21Map<Key, T>::value_type a,
                             typename S21Map<Key, T>::value_type b) {
  if (a.first > b.first) {
    return 1;
  }
  if (a.first < b.first) {
    return -1;
  }
  return 0;
}

}  // namespace s21

#endif