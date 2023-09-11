#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(MapTests, DefaultConstructor) {
  s21::S21Map<int, char> m;
  EXPECT_EQ(m.size(), 0);
  EXPECT_TRUE(m.empty());
}

TEST(MapTests, InitializerListConstructor) {
  s21::S21Map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.at(1), "one");
  EXPECT_EQ(m.at(2), "two");
  EXPECT_EQ(m.at(3), "three");
}

TEST(MapTests, CopyConstructor) {
  s21::S21Map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::S21Map<int, std::string> copy_m(m);
  EXPECT_EQ(copy_m.size(), 3);
  EXPECT_FALSE(copy_m.empty());
  EXPECT_EQ(copy_m.at(1), "one");
}

TEST(MapTests, constructorMove) {
  s21::S21Map<int, int> m1{{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::S21Map<int, int> m3{{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::S21Map<int, int> m2 = std::move(m1);
  EXPECT_EQ(m1.size(), 0);
  auto it1 = m2.begin();
  for (auto it2 = m3.begin(); it2 != m3.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(MapTests, operator_move) {
  s21::S21Map<int, int> map_empty;
  std::map<int, int> std_map_empty;
  s21::S21Map<int, int> map3{{10, 50}, {8, 60}, {6, 70}};
  std::map<int, int> std_map3{{10, 50}, {8, 60}, {6, 70}};
  map_empty = std::move(map3);
  std_map_empty = std::move(std_map3);
  for (const auto &pair : std_map_empty) {
    EXPECT_EQ(map_empty.at(pair.first), std_map_empty.at(pair.first));
  }
}

TEST(MapTests, InsertKeyValue) {
  s21::S21Map<int, std::string> map;
  map.insert(1, "one");
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  map.insert(2, "two");
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}

TEST(MapTests, InsertExist) {
  s21::S21Map<int, std::string> map;
  map.insert(1, "one");
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  map.insert(1, "two");
  EXPECT_EQ(map.size(), 1);
}

TEST(MapTests, InsertPair) {
  s21::S21Map<int, std::string> map;
  map.insert(std::make_pair(1, "one"));
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  map.insert(std::make_pair(2, "two"));
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}

TEST(MapTests, InsertOrAssign) {
  s21::S21Map<int, std::string> map;
  auto pair1 = map.insert_or_assign(1, "one");
  EXPECT_TRUE(pair1.second);
  auto pair = *(pair1.first);
  EXPECT_EQ(pair.first, 1);
  EXPECT_EQ(pair.second, "one");
  auto pair2 = map.insert_or_assign(1, "ONE");
  EXPECT_FALSE(pair2.second);
  auto pair3 = *(pair2.first);
  EXPECT_EQ(pair3.first, 1);
  EXPECT_EQ(pair3.second, "ONE");
  map.insert_or_assign(2, "two");
  map.insert_or_assign(3, "three");
  map.insert_or_assign(4, "four");
  map.insert_or_assign(5, "five");
  EXPECT_EQ(map.size(), 5);
  EXPECT_EQ(map[1], "ONE");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");
  EXPECT_EQ(map[4], "four");
  EXPECT_EQ(map[5], "five");
}

TEST(MapTests, InsertOrAssign2) {
  s21::S21Map<int, int> m1{{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2{{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.insert_or_assign(3, 1).second, m2.insert_or_assign(3, 1).second);
  EXPECT_EQ(m1.at(3), m2.at(3));
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(MapTests, InsertOrAssign3) {
  s21::S21Map<int, int> m1{{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2{{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.insert_or_assign(2, 1).second, m2.insert_or_assign(2, 1).second);
  EXPECT_EQ(m1.at(2), m2.at(2));
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(MapTests, AtAndOperatorBrackets) {
  s21::S21Map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_THROW(map.at(4), std::out_of_range);
}

TEST(MapTests, beginConst) {
  const s21::S21Map<int, int> m1{{1, 1}};
  const std::map<int, int> m2{{1, 1}};
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(MapTests, EmptyAndSize) {
  s21::S21Map<int, std::string> empty_map;
  s21::S21Map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_TRUE(empty_map.empty());
  EXPECT_EQ(empty_map.size(), 0);

  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 3);
}

TEST(MapTests, MaxSize) {
  s21::S21Map<int, std::string> map;
  std::map<int, std::string> map1;

  EXPECT_GT(map.max_size(), map1.max_size());
}

TEST(MapTests, iter_plus) {
  s21::S21Map<int, int> m11{{389, 12}, {3829, 12}, {111, 12}, {189, 12},
                            {11, 12},  {1, 1},     {2, 2},    {100, 3},
                            {4, 4},    {5, 5}};

  std::map<int, int> m12{{389, 12}, {3829, 12}, {111, 12}, {189, 12}, {11, 12},
                         {1, 1},    {2, 2},     {100, 3},  {4, 4},    {5, 5}};

  auto it2 = m12.begin();
  for (auto it = m11.begin(); it != m11.end(); it++, it2++) {
    EXPECT_EQ((*it).first, (*it2).first);
    EXPECT_EQ((*it).second, (*it2).second);
  }
}

TEST(MapTests, iter_plus_const) {
  const s21::S21Map<int, int> m11{{389, 12}, {3829, 12}, {111, 12}, {189, 12},
                                  {11, 12},  {1, 1},     {2, 2},    {100, 3},
                                  {4, 4},    {5, 5}};

  const std::map<int, int> m12{{389, 12}, {3829, 12}, {111, 12}, {189, 12},
                               {11, 12},  {1, 1},     {2, 2},    {100, 3},
                               {4, 4},    {5, 5}};

  auto it2 = m12.begin();
  for (auto it = m11.begin(); it != m11.end(); it++, it2++) {
    EXPECT_EQ((*it).first, (*it2).first);
    EXPECT_EQ((*it).second, (*it2).second);
  }
}

TEST(MapTests, iter_minus) {
  s21::S21Map<int, int> m11{{389, 12}, {3829, 12}, {111, 12}, {189, 12},
                            {11, 12},  {1, 1},     {2, 2},    {100, 3},
                            {4, 4},    {5, 5}};

  std::map<int, int> m12{{389, 12}, {3829, 12}, {111, 12}, {189, 12}, {11, 12},
                         {1, 1},    {2, 2},     {100, 3},  {4, 4},    {5, 5}};

  auto it = m11.begin();
  auto it2 = m12.begin();

  while ((*it).first != 3829) {
    it++;
    it2++;
  }

  for (; it != m11.begin(); it--, it2--) {
    EXPECT_EQ((*it).first, (*it2).first);
    EXPECT_EQ((*it).second, (*it2).second);
  }
}

TEST(MapTests, Erase) {
  s21::S21Map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  map.insert({5, "five"});

  auto it1 = map.begin();
  ++it1;
  map.erase(it1);
  EXPECT_EQ(map.size(), 3);
  EXPECT_FALSE(map.contains(2));
}

TEST(MapTests, Erase_1) {
  s21::S21Map<int, std::string> s21_map_1{
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::S21Map<int, std::string> s21_map_2{
      {1, "aboba"}, {3, "amogus"}, {4, "abobus"}};
  auto it = s21_map_1.begin();
  ++it;
  s21_map_1.erase(it);
  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(MapTests, Erase_2) {
  s21::S21Map<int, std::string> s21_map{
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};

  auto it = s21_map.begin();
  s21_map.erase(it);
  it = s21_map.begin();
  s21_map.erase(it);
  it = s21_map.begin();
  s21_map.erase(it);
  it = s21_map.begin();
  s21_map.erase(it);

  EXPECT_EQ(s21_map.empty(), true);
  EXPECT_EQ(s21_map.size(), size_t(0));

  s21_map.insert(1, "aboba");

  EXPECT_EQ(s21_map.empty(), false);
  EXPECT_EQ(s21_map.size(), size_t(1));
  EXPECT_EQ(s21_map.contains(1), true);
}

TEST(MapTests, Erase_3) {
  s21::S21Map<int, int> m1{{2, 2}};
  auto it = m1.begin();
  m1.erase(it);
  EXPECT_EQ(m1.contains(2), false);
  m1.insert({3, 2});
  EXPECT_EQ(m1.size(), 1);
}

TEST(MapTests, Swap) {
  s21::S21Map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::S21Map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});

  map1.swap(map2);

  EXPECT_EQ(map1.size(), 2);
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));

  EXPECT_EQ(map2.size(), 2);
  EXPECT_TRUE(map2.contains(1));
  EXPECT_TRUE(map2.contains(2));
}

TEST(MapTests, swapEmpty) {
  s21::S21Map<int, int> m1;
  std::map<int, int> m2;
  s21::S21Map<int, int> m11;
  std::map<int, int> m22;
  m1.swap(m11);
  m2.swap(m22);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(MapTests, Merge) {
  s21::S21Map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::S21Map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});

  map1.merge(map2);

  EXPECT_EQ(map1.size(), 4);
  EXPECT_TRUE(map1.contains(1));
  EXPECT_TRUE(map1.contains(2));
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));
}

TEST(MapTests, Merge2) {
  s21::S21Map<int, int> m1{{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2{{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  s21::S21Map<int, int> m11{{389, 12}, {3829, 12}, {111, 12}, {189, 12},
                            {11, 12},  {1, 1},     {2, 2},    {100, 3},
                            {4, 4},    {5, 5}};
  std::map<int, int> m22{{389, 12}, {3829, 12}, {111, 12}, {189, 12}, {11, 12},
                         {1, 1},    {2, 2},     {100, 3},  {4, 4},    {5, 5}};
  m1.merge(m11);
  m2.merge(m22);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m11.size(), m22.size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(MapTests, MergeEmpty) {
  s21::S21Map<int, int> s1;
  s21::S21Map<int, int> s2{{3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> s3;
  std::map<int, int> s4{{3, 3}, {4, 4}, {5, 5}};
  s1.merge(s2);
  s3.merge(s4);
  EXPECT_EQ(s1.size(), s3.size());
  EXPECT_TRUE(s1.contains(3));
  EXPECT_FALSE(s2.contains(3));
}

TEST(MapTests, operatorBrace) {
  s21::S21Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1[3], m2[3]);
  EXPECT_NO_THROW(m1[10] = 10);
  EXPECT_NO_THROW(m2[10] = 10);
  EXPECT_NO_THROW(m1.at(10) = 5);
  EXPECT_NO_THROW(m2.at(10) = 5);
  EXPECT_EQ(m1.at(10), m2.at(10));
}

TEST(MapTests, Contains) {
  s21::S21Map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}

TEST(MapTests, clear) {
  s21::S21Map<int, int> m1{{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2{{1, 1}, {2, 2}, {100, 3}, {4, 4}, {5, 5}};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}