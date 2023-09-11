#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(SetTests, DefaultConstructor) {
  s21::S21Set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(SetTests, InitializerListConstructor) {
  s21::S21Set<int> s{1, 2, 3};
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTests, CopyConstructor) {
  s21::S21Set<int> s1{1, 2, 3};
  s21::S21Set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(SetTests, MoveConstructor) {
  s21::S21Set<int> s1{1, 2, 3};
  s21::S21Set<int> s2(std::move(s1));
  std::set<int> std1{1, 2, 3};
  std::set<int> std2(std::move(std1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s1.size(), std1.size());
  EXPECT_EQ(s2.size(), std2.size());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTests, Begin) {
  s21::S21Set<int> s1{3, 5, 1, 4, 2};
  std::set<int> s2{3, 5, 1, 4, 2};
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  ASSERT_EQ(*it1, 1);
  ASSERT_EQ(*it1, *it2);

  s1.clear();
  ASSERT_EQ(s1.empty(), true);
  s2.clear();
  ASSERT_EQ(s2.empty(), true);
}

TEST(SetTests, SizeMaxSize) {
  s21::S21Set<int> s{3, 5, 1, 4, 2};
  std::set<int> s1{3, 5, 1, 4, 2};
  ASSERT_EQ(s.size(), 5);
  ASSERT_GE(s.max_size(), s1.max_size());

  s.clear();
  ASSERT_EQ(s.size(), 0);
}

TEST(SetTests, Swap) {
  s21::S21Set<int> s1{1, 2, 3};
  s21::S21Set<int> s2{4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s1.contains(4));
}

TEST(SetTests, Merge) {
  s21::S21Set<int> s1{1, 2, 3};
  s21::S21Set<int> s2{2, 3, 4, 5, 6};
  std::set<int> s3{1, 2, 3};
  std::set<int> s4{2, 3, 4, 5, 6};
  EXPECT_EQ(s2.size(), s4.size());
  s1.merge(s2);
  s3.merge(s4);

  EXPECT_EQ(s1.size(), s3.size());
  EXPECT_EQ(s2.size(), s4.size());
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTests, Find) {
  s21::S21Set<int> s{1, 2, 3};
  auto it1 = s.find(2);
  EXPECT_EQ(*it1, 2);
  auto it2 = s.find(4);
  EXPECT_EQ(it2, s.end());
}

TEST(SetTests, Erase) {
  s21::S21Set<int> s{1, 2, 3, 4, 5};
  auto it = s.find(3);
  s.erase(it);
  EXPECT_EQ(s.size(), 4);
  EXPECT_FALSE(s.contains(3));
}

TEST(SetTests, SET_MERGE_DIFFERENT_ELEMENTS) {
  s21::S21Set<int> S1{1, 3, 5};
  s21::S21Set<int> S2{2, 4, 6};
  std::set<int> S3{1, 3, 5, 2, 4, 6};
  std::set<int> empty;
  S1.merge(S2);
  ASSERT_EQ(S1.size(), 6);
  ASSERT_EQ(S2.size(), 0);
}

TEST(SetTests, SET_MERGE_IDENTICAL_ELEMENTS) {
  s21::S21Set<int> S1{1, 3, 5};
  s21::S21Set<int> S2{1, 3, 5};
  std::set<int> S3{1, 3, 5};
  S1.merge(S2);
  ASSERT_EQ(S1.size(), 3);
  ASSERT_EQ(S2.size(), 3);
}

TEST(SetTests, SET_MERGE_FIRST_EMPTY) {
  s21::S21Set<int> S1{};
  s21::S21Set<int> S2{1, 3, 5};
  S1.merge(S2);
  ASSERT_EQ(S1.size(), 3);
  ASSERT_EQ(S2.size(), 0);
}

TEST(SetTests, SET_MERGE_SECOND_EMPTY) {
  s21::S21Set<int> S1{1, 3, 5};
  s21::S21Set<int> S2{};
  S1.merge(S2);
  ASSERT_EQ(S1.size(), 3);
  ASSERT_EQ(S2.size(), 0);
}

TEST(SetTests, SET_FIND_EXISTING_ELEMENT) {
  s21::S21Set<int> S1{50, 25, 75, 10, 40, 5,  15, 35,
                      45, 80, 60, 70, 55, 90, 78};
  std::set<int> S2{50, 25, 75, 10, 40, 5, 15, 35, 45, 80, 60, 70, 55, 90, 78};
  auto it_S1 = S1.find(75);
  auto it_S2 = S2.find(75);
  ASSERT_EQ(*it_S1, *it_S2);
}

TEST(SetTests, SET_FIND_NOT_EXISTING_ELEMENT1) {
  s21::S21Set<int> S1{50, 25, 75, 10, 40, 5,  15, 35,
                      45, 80, 60, 70, 55, 90, 78};
  auto it_S1 = S1.find(43);
  ASSERT_EQ(it_S1, S1.end());
}

TEST(SetTests, SET_FIND_NOT_EXISTING_ELEMENT2) {
  s21::S21Set<int> S1{50, 25, 75, 10, 40, 5,  15, 35,
                      45, 80, 60, 70, 55, 90, 78};
  auto it_S1 = S1.find(0);
  ASSERT_EQ(it_S1, S1.end());
}

TEST(SetTests, AssignmentCopy) {
  s21::S21Set<int> S1{50, 25, 75};
  S1.insert(25);
  s21::S21Set<int> S2;
  S2 = S1;
  ASSERT_EQ(S2.size(), 4);
  ASSERT_EQ(S2.size(), S1.size());
}

TEST(SetTests, AssignmentMove) {
  s21::S21Set<int> S1{50, 25, 75};
  S1.insert(25);
  s21::S21Set<int> S2;
  S2 = std::move(S1);
  ASSERT_EQ(S2.size(), 4);
  ASSERT_EQ(S1.size(), 0);
}

TEST(SetTests, FindConst) {
  const s21::S21Set<int> S1{50, 25, 75};
  const std::set<int> S2{50, 25, 75};
  ASSERT_EQ(*(S2.find(75)), *(S1.find(75)));
}

TEST(SetTests, operator_move) {
  s21::S21Set<int> set_empty;
  std::set<int> std_set_empty;
  s21::S21Set<int> set3{10, 60, 70};
  std::set<int> std_set3{10, 60, 70};
  set_empty = std::move(set3);
  std_set_empty = std::move(std_set3);
  ASSERT_EQ(set_empty.size(), std_set_empty.size());
  ASSERT_EQ(set3.size(), std_set3.size());
}