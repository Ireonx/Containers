#include <gtest/gtest.h>

#include "../s21_containersplus.h"

TEST(MultisetTest, construct_il) {
  s21::S21Multiset<int> set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  std::multiset<int> std_set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  EXPECT_EQ(set.size(), std_set.size());
  auto it = set.begin();
  for (const auto &std_data : std_set) {
    EXPECT_EQ(*it, std_data);
    ++it;
  }
}

TEST(MultisetTest, construct_copy) {
  s21::S21Multiset<int> set3{10, 8, 8, 6};
  std::multiset<int> std_set3{10, 8, 8, 6};
  s21::S21Multiset<int> set4(set3);
  std::multiset<int> std_set4(std_set3);
  EXPECT_EQ(set4.size(), std_set4.size());
  auto it = set4.begin();
  for (const auto &std_data : std_set4) {
    EXPECT_EQ(*it, std_data);
    ++it;
  }
}

TEST(MultisetTest, construct_move) {
  s21::S21Multiset<int> set3{10, 8, 8, 6};
  std::multiset<int> std_set3{10, 8, 8, 6};
  s21::S21Multiset<int> set4(std::move(set3));
  std::multiset<int> std_set4(std::move(std_set3));
  auto it = set4.begin();
  for (const auto &std_data : std_set4) {
    EXPECT_EQ(*it, std_data);
    ++it;
  }
}

TEST(MultisetTest, operator_copy) {
  s21::S21Multiset<int> set_empty;
  std::multiset<int> std_set_empty;
  s21::S21Multiset<int> set3{10, 8, 8, 6};
  std::multiset<int> std_set3{10, 8, 8, 6};
  set_empty = set3;
  std_set_empty = std_set3;
  auto it = set_empty.begin();
  for (const auto &std_data : std_set_empty) {
    EXPECT_EQ(*it, std_data);
    ++it;
  }
}

TEST(MultisetTest, operator_move) {
  s21::S21Multiset<int> set_empty;
  std::multiset<int> std_set_empty;
  s21::S21Multiset<int> set3{10, 8, 8, 6};
  std::multiset<int> std_set3{10, 8, 8, 6};
  set_empty = std::move(set3);
  std_set_empty = std::move(std_set3);
  auto it = set_empty.begin();
  for (const auto &std_data : std_set_empty) {
    EXPECT_EQ(*it, std_data);
    ++it;
  }
}

TEST(MultisetTest, swap) {
  s21::S21Multiset<int> set_empty;
  std::multiset<int> std_set_empty;
  s21::S21Multiset<int> set3{10, 8, 8, 6};
  std::multiset<int> std_set3{10, 8, 8, 6};
  s21::S21Multiset<int> set5{15, 12, 20};
  std::multiset<int> std_set5{15, 12, 20};
  set3.swap(set5);
  std_set3.swap(std_set5);
  auto it = set3.begin();
  for (const auto &std_data : std_set3) {
    EXPECT_EQ(*it, std_data);
    ++it;
  }

  auto it2 = set5.begin();
  for (const auto &std_data : std_set5) {
    EXPECT_EQ(*it2, std_data);
    ++it2;
  }

  set_empty.swap(set5);
  std_set_empty.swap(std_set5);
  auto it3 = set5.begin();
  for (const auto &std_data : std_set5) {
    EXPECT_EQ(*it3, std_data);
    ++it3;
  }

  auto it4 = set_empty.begin();
  for (const auto &std_data : std_set_empty) {
    EXPECT_EQ(*it4, std_data);
    ++it4;
  }
}

TEST(MultisetTest, size) {
  s21::S21Multiset<int> set_empty;
  std::multiset<int> std_set_empty;
  EXPECT_EQ(set_empty.size(), std_set_empty.size());
}

TEST(MultisetTest, clear) {
  s21::S21Multiset<int> set_empty;
  std::multiset<int> std_set_empty;
  s21::S21Multiset<int> set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  std::multiset<int> std_set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  EXPECT_EQ(set.size(), std_set.size());
  EXPECT_EQ(set_empty.size(), std_set_empty.size());
  set.clear();
  std_set.clear();
  set_empty.clear();
  std_set_empty.clear();
  EXPECT_EQ(set_empty.size(), std_set_empty.size());
  EXPECT_EQ(set.size(), std_set.size());
}

TEST(MultisetTest, it_begin) {
  s21::S21Multiset<int> set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  std::multiset<int> std_set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  auto it = set.begin();
  auto std_it = std_set.begin();
  EXPECT_EQ(*it, *std_it);
}

TEST(MultisetTest, it_end) {
  s21::S21Multiset<int> set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  std::multiset<int> std_set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  auto it = set.end();
  auto std_it = std_set.end();
  --std_it;
  EXPECT_NO_THROW(--it;);
}

TEST(MultisetTest, empty) {
  s21::S21Multiset<int> set_empty;
  std::multiset<int> std_set_empty;
  EXPECT_TRUE(set_empty.empty());
  EXPECT_TRUE(std_set_empty.empty());
}

TEST(MultisetTest, insert) {
  s21::S21Multiset<int> set_empty;
  std::multiset<int> std_set_empty;
  s21::S21Multiset<std::string> set_s;
  std::multiset<std::string> std_set_s;
  set_s.insert("25");
  set_s.insert("55");
  set_s.insert("55");
  set_empty.insert(25);
  set_empty.insert(55);
  set_empty.insert(55);
  std_set_s.insert("25");
  std_set_s.insert("55");
  std_set_s.insert("55");
  std_set_empty.insert(25);
  std_set_empty.insert(55);
  std_set_empty.insert(55);

  auto it2 = set_s.begin();
  for (const auto &std_data : std_set_s) {
    EXPECT_EQ(*it2, std_data);
    ++it2;
  }

  auto it3 = set_empty.begin();
  for (const auto &std_data : std_set_empty) {
    EXPECT_EQ(*it3, std_data);
    ++it3;
  }
  EXPECT_EQ(set_s.size(), std_set_s.size());
}

TEST(MultisetTest, erase) {
  s21::S21Multiset<std::string> set_s;
  std::multiset<std::string> std_set_s;
  set_s.insert("1");
  set_s.insert("2");
  std_set_s.insert("1");
  std_set_s.insert("2");
  set_s.erase((set_s.begin()));
  std_set_s.erase((std_set_s.begin()));

  auto it2 = set_s.begin();
  for (const auto &std_data : std_set_s) {
    EXPECT_EQ(*it2, std_data);
    ++it2;
  }
}

TEST(MultisetTest, merge) {
  s21::S21Multiset<std::string> ma_{"apple", "x", "banana"};
  s21::S21Multiset<std::string> mb_{"zorro", "x", "batman", "alpaca"};
  s21::S21Multiset<std::string> u_;
  std::multiset<std::string> ma{"apple", "x", "banana"};
  std::multiset<std::string> mb{"zorro", "x", "batman", "alpaca"};
  std::multiset<std::string> std_u;
  u_.merge(ma_);
  std_u.merge(ma);
  EXPECT_EQ(ma_.size(), ma.size());
  EXPECT_EQ(u_.size(), std_u.size());
  u_.merge(mb_);
  std_u.merge(mb);
  EXPECT_EQ(mb_.size(), mb.size());
  EXPECT_EQ(u_.size(), std_u.size());
  EXPECT_EQ(*(u_.begin()), *std_u.begin());

  auto it2 = u_.begin();
  for (const auto &std_data : std_u) {
    EXPECT_EQ(*it2, std_data);
    ++it2;
  }
}

TEST(MultisetTest, contains) {
  s21::S21Multiset<char> example{'a', 'b'};
  EXPECT_TRUE(example.contains('a'));
  EXPECT_FALSE(example.contains('t'));
}

TEST(MultisetTest, find) {
  s21::S21Multiset<int> set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  std::multiset<int> std_set{1, 1, 1, 0, 0, 4, 4, 7, -5};

  auto iter = set.find(4);
  auto iter2 = std_set.find(4);
  int a = *iter, b = *iter2;
  EXPECT_TRUE(a == b);

  iter = set.find(123);
  iter2 = std_set.find(123);
  EXPECT_TRUE(iter == set.end());
  EXPECT_TRUE(iter2 == std_set.end());
}

TEST(MultisetTest, lower_bound) {
  s21::S21Multiset<int> set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  std::multiset<int> std_set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  s21::S21Multiset<int> set_empty;
  std::multiset<int> std_set_empty;
  auto iter = set.lower_bound(1);
  auto std_iter = std_set.lower_bound(1);
  EXPECT_TRUE(*iter == *std_iter);

  auto iter2 = set_empty.lower_bound(1);
  auto std_iter2 = std_set_empty.lower_bound(1);
  EXPECT_EQ(iter2, set_empty.end());
  EXPECT_EQ(std_iter2, std_set_empty.end());

  auto iter3 = set_empty.lower_bound(111);
  auto std_iter3 = std_set_empty.lower_bound(111);
  EXPECT_EQ(iter3, set_empty.end());
  EXPECT_EQ(std_iter3, std_set_empty.end());
}

TEST(MultisetTest, upper_bound) {
  s21::S21Multiset<int> set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  std::multiset<int> std_set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  s21::S21Multiset<int> set_empty;
  std::multiset<int> std_set_empty;
  auto iter = set.upper_bound(1);
  auto std_iter = std_set.upper_bound(1);
  EXPECT_EQ((*iter), *std_iter);

  auto iter2 = set_empty.upper_bound(1);
  auto std_iter2 = std_set_empty.upper_bound(1);
  EXPECT_EQ(iter2, set_empty.end());
  EXPECT_EQ(std_iter2, std_set_empty.end());

  auto iter3 = set_empty.upper_bound(111);
  auto std_iter3 = std_set_empty.upper_bound(111);
  EXPECT_EQ(iter3, set_empty.end());
  EXPECT_EQ(std_iter3, std_set_empty.end());
}

TEST(MultisetTest, count) {
  s21::S21Multiset<int> set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  std::multiset<int> std_set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  s21::S21Multiset<int> set_empty;
  std::multiset<int> std_set_empty;
  EXPECT_EQ(set.count(1), std_set.count(1));
  EXPECT_EQ(set_empty.count(1), std_set_empty.count(1));
  EXPECT_EQ(set.count(111), std_set.count(111));
}

TEST(MultisetTest, equal_range) {
  s21::S21Multiset<int> set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  std::multiset<int> std_set{1, 1, 1, 0, 0, 4, 4, 7, -5};
  s21::S21Multiset<int> set_empty;
  std::multiset<int> std_set_empty;
  auto pr = set.equal_range(1);
  auto std_pr = std_set.equal_range(1);
  EXPECT_EQ(*(pr.first), *std_pr.first);
  EXPECT_EQ(*(pr.second), *std_pr.second);

  auto pr2 = set_empty.equal_range(1);
  auto std_pr2 = std_set_empty.equal_range(1);
  EXPECT_EQ(pr2.first, set_empty.end());
  EXPECT_EQ(pr2.second, set_empty.end());
  EXPECT_EQ(std_pr2.first, std_set_empty.end());
  EXPECT_EQ(std_pr2.second, std_set_empty.end());

  auto pr3 = set_empty.equal_range(111);
  auto std_pr3 = std_set_empty.equal_range(111);
  EXPECT_EQ(pr3.first, set_empty.end());
  EXPECT_EQ(pr3.second, set_empty.end());
  EXPECT_EQ(std_pr3.first, std_set_empty.end());
  EXPECT_EQ(std_pr3.second, std_set_empty.end());
}

TEST(MultisetTest, allcase) {
  s21::S21Multiset<int> my_multiset;
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  my_multiset.insert(10);
  EXPECT_EQ(my_multiset.size(), 10U);
  auto it = my_multiset.begin();
  my_multiset.erase(it);
  EXPECT_EQ(my_multiset.size(), 9U);
  it = my_multiset.begin();
  EXPECT_EQ(*it, 10);
  my_multiset.erase(it);
  EXPECT_EQ(my_multiset.size(), 8U);
}
