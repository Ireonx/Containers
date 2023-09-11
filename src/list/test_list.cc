#include <gtest/gtest.h>

#include <list>

#include "../s21_containers.h"

TEST(listTest, DefaultConstructor) {
  s21::S21List<int> A;
  EXPECT_EQ(0, A.size());
  EXPECT_EQ(true, A.empty());
}

TEST(listTest, ParamConstructor_1) {
  s21::S21List<int> A{1};
  EXPECT_EQ(1, A.size());
  EXPECT_EQ(false, A.empty());
}

TEST(listTest, ParamConstructor_2) {
  s21::S21List<int> A{1, 2};
  EXPECT_EQ(2, A.size());
  EXPECT_EQ(false, A.empty());
}
TEST(listTest, Constructor_Initializer_list) {
  s21::S21List<int> s21_list{1, 2, 3, 4};
  std::list<int> std_list{1, 2, 3, 4};
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(listTest, Constructor_Parameterized) {
  s21::S21List<double> s21_list(5);
  std::list<double> std_list(5);
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(listTest, Constructor_Copy) {
  s21::S21List<char> s21_list_1{'a', 'b', 'c', 'd'};
  std::list<char> std_list_1{'a', 'b', 'c', 'd'};
  s21::S21List<char> s21_list_2(s21_list_1);
  std::list<char> std_list_2(std_list_1);

  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
  EXPECT_EQ(std_list_1.size(), std_list_2.size());
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(listTest, Constructor_Move) {
  s21::S21List<char> s21_list_1{'a', 'b', 'c', 'd'};
  std::list<char> std_list_1{'a', 'b', 'c', 'd'};
  s21::S21List<char> s21_list_2 = std::move(s21_list_1);
  std::list<char> std_list_2 = std::move(std_list_1);

  EXPECT_EQ(s21_list_2.size(), std_list_2.size());
  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
  EXPECT_EQ(s21_list_1.empty(), std_list_1.empty());
  auto it1 = s21_list_2.begin();
  auto it2 = std_list_2.begin();
  while (it1 != s21_list_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(listTest, Modifier_Insert) {
  s21::S21List<int> s21_list_1{'a', 'c', 'd'};
  s21::S21List<int> s21_list_2{'a', 'b', 'c', 'd'};

  auto it = s21_list_1.begin();
  ++it;
  s21_list_1.insert(it, 'b');
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(listTest, Modifier_Erase) {
  s21::S21List<int> s21_list_1{'a', 'c', 'd'};
  s21::S21List<int> s21_list_2{'a', 'b', 'c', 'd'};

  auto it = s21_list_2.begin();
  ++it;
  s21_list_2.erase(it);
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(listTest, Modifier_Push) {
  s21::S21List<int> s21_list{1, 2, 3, 4};
  std::list<int> std_list{1, 2, 3, 4};
  s21_list.push_back(5);
  s21_list.push_front(0);
  std_list.push_back(5);
  std_list.push_front(0);
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(listTest, Modifier_Pop) {
  s21::S21List<int> s21_list{1, 2, 3, 4};
  std::list<int> std_list{1, 2, 3, 4};
  s21_list.pop_back();
  s21_list.pop_front();
  std_list.pop_back();
  std_list.pop_front();
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(listTest, Modifier_Sort) {
  s21::S21List<int> s21_list{-5, -4, -3, -2, -1};
  std::list<int> std_list{-5, -4, -3, -2, -1};
  s21_list.sort();
  std_list.sort();
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(listTest, Modifier_Swap) {
  s21::S21List<char> s21_list_1{'a', 'b', 'o', 'b', 'a'};
  s21::S21List<char> s21_list_2{'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21::S21List<char> s21_list_3{'a', 'b', 'o', 'b', 'a'};
  s21::S21List<char> s21_list_4{'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21_list_1.swap(s21_list_2);
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  auto it3 = s21_list_3.begin();
  auto it4 = s21_list_4.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_list_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_4.size());
  EXPECT_EQ(s21_list_2.size(), s21_list_3.size());
}

TEST(listTest, Modifier_Merge) {
  s21::S21List<int> s21_list_1{1, 3, 7};
  s21::S21List<int> s21_list_2{-1, 0, 5, 8};
  std::list<int> std_list_1{1, 3, 7};
  std::list<int> std_list_2{-1, 0, 5, 8};
  s21_list_1.merge(s21_list_2);
  std_list_1.merge(std_list_2);
  auto it1 = s21_list_1.begin();
  auto it2 = std_list_1.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
}

TEST(listTest, Modifier_Merge_equal) {
  s21::S21List<int> s21_list_1{1, 3, 7};
  std::list<int> std_list_1{1, 3, 7};
  s21_list_1.merge(s21_list_1);
  std_list_1.merge(std_list_1);
  auto it1 = s21_list_1.begin();
  auto it2 = std_list_1.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
}

TEST(listTest, Modifier_Merge_not_sorted) {
  s21::S21List<int> s21_list_1{-1, 10, 0, -100};
  s21::S21List<int> s21_list_2{-4, 1, 0, -10};
  std::list<int> std_list_1{-1, 10, 0, -100};
  std::list<int> std_list_2{-4, 1, 0, -10};
  s21_list_1.merge(s21_list_2);
  std_list_1.merge(std_list_2);
  auto it1 = s21_list_1.begin();
  auto it2 = std_list_1.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
}

TEST(listTest, Modifier_Reverse) {
  s21::S21List<int> s21_list_1{1, 2, 3, 4};
  s21::S21List<int> s21_list_2{4, 3, 2, 1};
  s21_list_1.reverse();
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(listTest, Modifier_Unique) {
  s21::S21List<int> s21_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  std::list<int> std_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  s21_list.unique();
  std_list.unique();
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list.size(), std_list.size());
}
