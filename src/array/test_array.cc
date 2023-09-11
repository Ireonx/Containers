#include <array>

#include "../s21_containersplus.h"
#include "gtest/gtest.h"

TEST(arrayTest, DefaultConstructor) {
  s21::S21Array<int, 0> A;
  EXPECT_EQ(0, A.size());
  EXPECT_EQ(true, A.empty());
}

TEST(arrayTest, ParamConstructor_1) {
  s21::S21Array<int, 1> A{1};
  EXPECT_EQ(1, A.size());
  EXPECT_EQ(false, A.empty());
}

TEST(arrayTest, ParamConstructor_2) {
  s21::S21Array<int, 2> A{1, 2};
  EXPECT_EQ(2, A.size());
  EXPECT_EQ(false, A.empty());
}

TEST(arrayTest, Constructor_Initializer_array) {
  s21::S21Array<int, 4> s21_array{1, 2, 3, 4};
  std::array<int, 4> std_array{1, 2, 3, 4};
  EXPECT_EQ(s21_array.front(), std_array.front());
  EXPECT_EQ(s21_array.back(), std_array.back());
  EXPECT_EQ(s21_array.size(), 4);
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(arrayTest, Constructor_Move) {
  s21::S21Array<char, 4> s21_array_1{'a', 'b', 'c', 'd'};
  s21::S21Array<char, 4> s21_array_2 = std::move(s21_array_1);
  s21::S21Array<char, 4> s21_array_3{'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_array_2.size(), 4);
  EXPECT_EQ(s21_array_1.size(), 4);
  EXPECT_EQ(s21_array_1.empty(), false);
  auto it1 = s21_array_2.begin();
  auto it2 = s21_array_3.begin();
  while (it1 != s21_array_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(arrayTest, Modifier_Swap) {
  s21::S21Array<char, 3> s21_array_1{'a', 'b', 'c'};
  s21::S21Array<char, 3> s21_array_2{'x', 'y', 'z'};
  s21::S21Array<char, 3> s21_array_3{'a', 'b', 'c'};
  s21::S21Array<char, 3> s21_array_4{'x', 'y', 'z'};
  s21_array_1.swap(s21_array_2);
  auto it1 = s21_array_1.begin();
  auto it2 = s21_array_2.begin();
  auto it3 = s21_array_3.begin();
  auto it4 = s21_array_4.begin();
  while (it1 != s21_array_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_array_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_array_1.size(), s21_array_4.size());
  EXPECT_EQ(s21_array_2.size(), s21_array_3.size());
}
