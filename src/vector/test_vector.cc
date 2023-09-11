#include <gtest/gtest.h>

#include <vector>

#include "../s21_containers.h"

TEST(VectorTest, Constructor_default) {
  s21::S21Vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.data(), std_v.data());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Constructor_n) {
  s21::S21Vector<int> s21_v(5);
  std::vector<int> std_v(5);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Constructor_initializer_list_1) {
  s21::S21Vector<int> s21_v{2, 3, 5, 7, 1};
  std::vector<int> std_v{2, 3, 5, 7, 1};
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));
}

TEST(VectorTest, Constructor_initializer_list_2) {
  std::initializer_list<int> b;
  s21::S21Vector<int> s21_v{b};
  std::vector<int> std_v{b};
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Constructor_copy_1) {
  s21::S21Vector<int> s21_v{2, 3, 5, 7, 1};
  std::vector<int> std_v{2, 3, 5, 7, 1};
  s21::S21Vector<int> s21_copy(s21_v);
  std::vector<int> std_copy(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_v.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
  EXPECT_EQ(s21_copy.at(0), std_copy.at(0));
  EXPECT_EQ(s21_copy.at(1), std_copy.at(1));
  EXPECT_EQ(s21_copy.at(2), std_copy.at(2));
  EXPECT_EQ(s21_copy.at(3), std_copy.at(3));
  EXPECT_EQ(s21_copy.at(4), std_copy.at(4));
}

TEST(VectorTest, Constructor_copy_2) {
  s21::S21Vector<int> s21_v;
  s21::S21Vector<int> s21_copy(s21_v);
  std::vector<int> std_v;
  std::vector<int> std_copy(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
}

TEST(VectorTest, Constructor_Move) {
  s21::S21Vector<char> s21_vector_1{'a', 'b', 'c', 'd'};
  std::vector<char> std_vector_1{'a', 'b', 'c', 'd'};
  s21::S21Vector<char> s21_vector_2 = std::move(s21_vector_1);
  std::vector<char> std_vector_2 = std::move(std_vector_1);

  EXPECT_EQ(s21_vector_2.size(), std_vector_2.size());
  EXPECT_EQ(s21_vector_1.size(), std_vector_1.size());
  EXPECT_EQ(s21_vector_1.empty(), std_vector_1.empty());
  auto it1 = s21_vector_2.begin();
  auto it2 = std_vector_2.begin();
  while (it1 != s21_vector_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(VectorTest, Operator_move_1) {
  s21::S21Vector<int> s21_v1{1, 2, 3};
  s21::S21Vector<int> s21_v2;
  s21_v2 = std::move(s21_v1);
  EXPECT_EQ(s21_v2.size(), 3);
  EXPECT_EQ(s21_v2.at(0), 1);
  EXPECT_EQ(s21_v2.at(1), 2);
  EXPECT_EQ(s21_v2.at(2), 3);
}

TEST(VectorTest, Operator_move_2) {
  s21::S21Vector<int> s21_v1{1, 2, 3};
  s21::S21Vector<int> s21_v2{4, 5, 6};
  s21_v2 = std::move(s21_v1);
  EXPECT_EQ(s21_v2.size(), 3);
  EXPECT_EQ(s21_v2.at(0), 1);
  EXPECT_EQ(s21_v2.at(1), 2);
  EXPECT_EQ(s21_v2.at(2), 3);
}

TEST(VectorTest, Element_at) {
  s21::S21Vector<int> s21_v{1, 2, 3, 4, 5};
  std::vector<int> std_v{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));
}

TEST(VectorTest, Element_at_throw) {
  s21::S21Vector<int> s21_v;
  bool res = true;
  try {
    s21_v.at(1);
  } catch (...) {
    res = false;
  }
  EXPECT_EQ(res, false);
}

TEST(VectorTest, Element_front) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  EXPECT_EQ(s21_v.front(), std_v.front());
}

TEST(VectorTest, Element_front_throw) {
  s21::S21Vector<int> s21_v;
  bool res = true;
  try {
    s21_v.front();
  } catch (...) {
    res = false;
  }
  EXPECT_EQ(res, false);
}

TEST(VectorTest, Element_back) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  EXPECT_EQ(s21_v.back(), std_v.back());
}

TEST(VectorTest, Element_back_throw) {
  s21::S21Vector<int> s21_v;
  bool res = true;
  try {
    s21_v.back();
  } catch (...) {
    res = false;
  }
  EXPECT_EQ(res, false);
}

TEST(VectorTest, Element_operator_square_brackets) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
}

TEST(VectorTest, Element_data) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(*s21_v.data(), *std_v.data());
}

TEST(VectorTest, Capacity_empty_1) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Capacity_empty_2) {
  s21::S21Vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Capacity_size_1) {
  s21::S21Vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Capacity_size_2) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Capacity_capacity_1) {
  s21::S21Vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_capacity_2) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_1) {
  s21::S21Vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.reserve(2);
  std_v.reserve(2);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_2) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(2);
  std_v.reserve(2);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_3) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(10);
  std_v.reserve(10);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_4_throw) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  bool res = true;
  try {
    s21_v.reserve(-2);
  } catch (...) {
    res = false;
  }
  EXPECT_EQ(res, false);
}

TEST(VectorTest, Capacity_shrink_to_fit_1) {
  s21::S21Vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.reserve(10);
  std_v.reserve(10);
  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_shrink_to_fit_2) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(10);
  std_v.reserve(10);
  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, clear_1) {
  s21::S21Vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, clear_2) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, insert_1) {
  s21::S21Vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.insert(s21_v.begin() + 1, 5);
  std_v.insert(std_v.begin() + 1, 5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
}

TEST(VectorTest, insert_2) {
  s21::S21Vector<int> s21_v{50, 10, 40, 20, 30};
  std::vector<int> std_v{50, 10, 40, 20, 30};
  s21_v.insert(s21_v.begin() + s21_v.size(), 100);
  std_v.insert(std_v.begin() + std_v.size(), 100);

  EXPECT_EQ(s21_v.at(5), std_v.at(5));
}

TEST(VectorTest, Insert) {
  s21::S21Vector<int> s21_vector_1{'a', 'c', 'd'};
  s21::S21Vector<int> s21_vector_2{'a', 'b', 'c', 'd'};

  auto it = s21_vector_1.begin();
  ++it;
  s21_vector_1.insert(it, 'b');
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
  s21_vector_1.insert(s21_vector_1.end(), '5');
  EXPECT_EQ(s21_vector_1.back(), '5');
}

TEST(VectorTest, push_back_1) {
  s21::S21Vector<int> s21_v;
  std::vector<int> std_v;

  s21_v.push_back(2);
  s21_v.push_back(3);
  s21_v.push_back(4);
  s21_v.push_back(5);

  std_v.push_back(2);
  std_v.push_back(3);
  std_v.push_back(4);
  std_v.push_back(5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorTest, push_back_2) {
  s21::S21Vector<int> s21_v{1, 2};
  std::vector<int> std_v{1, 2};

  s21_v.push_back(2);
  s21_v.push_back(3);
  s21_v.push_back(4);
  s21_v.push_back(5);

  std_v.push_back(2);
  std_v.push_back(3);
  std_v.push_back(4);
  std_v.push_back(5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));
  EXPECT_EQ(s21_v.at(5), std_v.at(5));
}

TEST(VectorTest, swap_1) {
  s21::S21Vector<int> s21_v;
  s21::S21Vector<int> s21_v_copy;

  std::vector<int> std_v;
  std::vector<int> std_v_copy;

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, swap_2) {
  s21::S21Vector<int> s21_v{1, 2, 3, 4};
  s21::S21Vector<int> s21_v_copy;

  std::vector<int> std_v{1, 2, 3, 4};
  std::vector<int> std_v_copy;

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, swap_3) {
  s21::S21Vector<int> s21_v{1, 2, 3, 4};
  s21::S21Vector<int> s21_v_copy{1, 2};

  std::vector<int> std_v{1, 2, 3, 4};
  std::vector<int> std_v_copy{1, 2};

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, swap_4) {
  s21::S21Vector<int> s21_v{1, 2, 3, 4};
  s21::S21Vector<int> s21_v_copy{1, 2, 3, 4, 5, 6};

  std::vector<int> std_v{1, 2, 3, 4};
  std::vector<int> std_v_copy{1, 2, 3, 4, 5, 6};

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, erase_1) {
  s21::S21Vector<int> s21_v{1, 2, 3, 4};
  std::vector<int> std_v{1, 2, 3, 4};

  s21_v.erase(s21_v.begin() + 1);
  std_v.erase(std_v.begin() + 1);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
}

TEST(VectorTest, erase_2) {
  s21::S21Vector<int> s21_v{50, 10, 40, 20, 30};
  std::vector<int> std_v{50, 10, 40, 20, 30};
  s21_v.erase(s21_v.begin());
  std_v.erase(std_v.begin());

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorTest, erase_3) {
  s21::S21Vector<int> s21_v{50, 10, 40, 20, 30};
  std::vector<int> std_v{50, 10, 40, 20, 30};
  s21_v.erase(s21_v.end() - 1);
  std_v.erase(std_v.end() - 1);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorTest, pop_back_1) {
  s21::S21Vector<int> s21_v{1, 2};

  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();

  EXPECT_EQ(s21_v.size(), 0);
  EXPECT_EQ(s21_v.capacity(), 2);
}

TEST(VectorTest, pop_back_2) {
  s21::S21Vector<int> s21_v;

  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();

  EXPECT_EQ(s21_v.size(), 0);
  EXPECT_EQ(s21_v.capacity(), 0);
}

TEST(VectorTest, Default) {
  s21::S21Vector<double> v1;
  EXPECT_EQ(0, v1.size());
}

TEST(VectorTest, With_parameter) {
  s21::S21Vector<int> v1(4);
  EXPECT_EQ(4, v1.size());
  EXPECT_EQ(4, v1.capacity());

  EXPECT_ANY_THROW(s21::S21Vector<int> v2(-4));
}

TEST(VectorTest, Initializer_list) {
  std::vector<double> v1{1, 2, 3, 4.356, 5.0};
  s21::S21Vector<double> v2{1, 2, 3, 4.356, 5.0};

  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], v2[i]);
  }
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(VectorTest, Copy) {
  s21::S21Vector<int> v2{1, 2, 3, 4, 5};
  s21::S21Vector<int> v1(v2);

  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1.at(i), v1.at(i));
  }
}

TEST(VectorTest, Move) {
  s21::S21Vector<int> v2{1, 2, 3, 4, 5};
  s21::S21Vector<int> v1(v2);

  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1.at(i), v1.at(i));
  }
}

TEST(VectorTest, Assign_operator) {
  s21::S21Vector<int> v2{1, 2, 3, 4, 5};
  s21::S21Vector<int> v1 = v2;

  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1.at(i), v1.at(i));
  }
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(VectorTest, At) {
  std::vector<double> v1{1.366, 2, 3};
  s21::S21Vector<double> v2{1.366, 2, 3};

  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1.at(i), v2.at(i));
  }
  try {
    EXPECT_ANY_THROW(v2.at(-25));
    EXPECT_ANY_THROW(v2.at(3));
  } catch (...) {
  }
}

TEST(VectorTest, Brackets) {
  std::vector<double> v1{1.366, 2, 3};
  s21::S21Vector<double> v2{1.366, 2, 3};

  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], v2[i]);
  }
}

TEST(VectorTest, Front_and_back) {
  std::vector<double> v1{1.366, 2, 3};
  s21::S21Vector<double> v2{1.366, 2, 3};

  EXPECT_EQ(v1.front(), v2.front());
  EXPECT_EQ(v1.back(), v2.back());
}

TEST(VectorTest, Data) {
  s21::S21Vector<int> v1;

  EXPECT_EQ(v1.data(), nullptr);

  std::vector<double> v2{1.366, 2, 3, 4, 5};
  s21::S21Vector<double> v3{1.366, 2, 3, 4, 5};

  EXPECT_EQ(*v2.data(), *v3.data());
}

TEST(VectorTest, Begin) {
  std::vector<int> v1{1, 2, 3, 4, 5};
  s21::S21Vector<int> v2{1, 2, 3, 4, 5};
  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  EXPECT_EQ(*iter1, *iter2);
}

TEST(VectorTest, End) {
  std::vector<int> v1{1, 2, 3, 4, 5};
  s21::S21Vector<int> v2{1, 2, 3, 4, 5};
  auto iter1 = v1.end();
  auto iter2 = v2.end();

  EXPECT_EQ(*(iter1 - 1), *(iter2 - 1));
}

TEST(VectorTest, Empty) {
  std::vector<int> v1{1, 2, 3, 4, 5};
  s21::S21Vector<int> v2{1, 2, 3, 4, 5};

  EXPECT_EQ(v1.empty(), v2.empty());

  std::vector<int> v3{};
  s21::S21Vector<int> v4{};

  EXPECT_EQ(v3.empty(), v4.empty());
}

TEST(VectorTest, Size) {
  std::vector<int> v1{1, 2, 3, 4, 5};
  s21::S21Vector<int> v2{1, 2, 3, 4, 5};

  EXPECT_EQ(v1.size(), v2.size());

  std::vector<int> v3;
  s21::S21Vector<int> v4;

  EXPECT_EQ(v3.size(), v4.size());
}

TEST(VectorTest, Max_size) {
  std::vector<int> v1{1, 2, 3, 4, 5};
  s21::S21Vector<int> v2{1, 2, 3, 4, 5};

  EXPECT_EQ(v1.max_size(), v2.max_size());
}

TEST(VectorTest, Reserve_and_capacity) {
  std::vector<int> v1{1, 2, 3, 4, 5};
  s21::S21Vector<int> v2{1, 2, 3, 4, 5};
  v1.reserve(30);
  v2.reserve(30);

  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(VectorTest, Shrink_to_fit) {
  std::vector<int> v1{1, 2, 3, 4, 5};
  s21::S21Vector<int> v2{1, 2, 3, 4, 5};
  v1.shrink_to_fit();
  v2.shrink_to_fit();

  EXPECT_EQ(v1.size(), v1.capacity());
  EXPECT_EQ(v2.size(), v2.capacity());
}

TEST(VectorTest, Clear) {
  std::vector<int> v1{1, 2, 3, 4, 5};
  s21::S21Vector<int> v2{1, 2, 3, 4, 5};
  v1.clear();
  v2.clear();

  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(VectorTest, Insert2) {
  std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::S21Vector<int> v2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto iter1 = v1.end();
  auto iter2 = v2.end();
  v1.insert(iter1, 11);
  v2.insert(iter2, 11);
  EXPECT_EQ(v1[10], v2[10]);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());

  iter1 = v1.begin();
  iter2 = v2.begin();
  v1.insert(iter1 + 5, 11);
  v2.insert(iter2 + 5, 11);
  EXPECT_EQ(v1[5], v2[5]);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(VectorTest, Erase) {
  std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::S21Vector<int> v2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto iter1 = v1.end();
  auto iter2 = v2.end();
  v1.erase(iter1 - 1);
  v2.erase(iter2 - 1);
  EXPECT_EQ(v1[8], v2[8]);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());

  iter1 = v1.begin();
  iter2 = v2.begin();
  v1.erase(iter1);
  v2.erase(iter2);
  EXPECT_EQ(v1[0], v2[0]);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());

  std::vector<int> v3{0};
  s21::S21Vector<int> v4{0};
  auto iter3 = v3.begin();
  auto iter4 = v4.begin();
  v3.erase(iter3);
  v4.erase(iter4);
  EXPECT_EQ(v3.size(), v4.size());
  EXPECT_EQ(v3.capacity(), v4.capacity());
}

TEST(VectorTest, Push_back) {
  std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::S21Vector<int> v2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  v1.push_back(11);
  v2.push_back(11);
  EXPECT_EQ(v1[10], v2[10]);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());

  std::vector<int> v3{};
  s21::S21Vector<int> v4{};
  v3.push_back(11);
  v4.push_back(11);
  EXPECT_EQ(v3[0], v4[0]);
  EXPECT_EQ(v3.size(), v4.size());
  EXPECT_EQ(v3.capacity(), v4.capacity());
}

TEST(VectorTest, Pop_back) {
  std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::S21Vector<int> v2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  v1.pop_back();
  v2.pop_back();
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());

  std::vector<int> v3;
  s21::S21Vector<int> v4;
  v3.pop_back();
  v4.pop_back();
  EXPECT_EQ(v3.capacity(), v4.capacity());
}

TEST(VectorTest, Swap) {
  std::vector<int> v1{1, 2, 3, 9};
  std::vector<int> v2{4, 5, 6};
  v1.swap(v2);
  s21::S21Vector<int> v3{1, 2, 3, 9};
  s21::S21Vector<int> v4{4, 5, 6};
  v3.swap(v4);

  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1.at(i), v3.at(i));
    EXPECT_EQ(v2.at(i), v4.at(i));
  }
}

TEST(VectorTest, operator_dereferencing) {
  std::vector<int> v1{1, 2, 3, 9};
  s21::S21Vector<int> v2{1, 2, 3, 9};
  auto x = v2.begin();
  x++;
  EXPECT_EQ(*++v1.begin(), *x);
}

TEST(VectorTest, operator_plusplus) {
  std::vector<int> v1{1, 2, 3, 9};
  s21::S21Vector<int> v2{1, 2, 3, 9};
  auto x = v2.begin();
  EXPECT_EQ(*++v1.begin(), *++x);
}

TEST(VectorTest, operator_minusminus) {
  std::vector<int> v1{1, 2, 3, 9};
  s21::S21Vector<int> v2{1, 2, 3, 9};
  auto x = v2.end();
  EXPECT_EQ(*--v1.end(), *--x);
}

TEST(VectorTest, operator_equal) {
  s21::S21Vector<int> v1{1, 2, 3, 9};
  EXPECT_TRUE(v1.begin() == v1.begin());
  EXPECT_FALSE(v1.begin() == v1.end());
}

TEST(VectorTest, operator_not_equal) {
  s21::S21Vector<int> v1{1, 2, 3, 9};
  EXPECT_FALSE(v1.begin() != v1.begin());
  EXPECT_TRUE(v1.begin() != v1.end());
}

TEST(VectorTest, insert_many_back) {
  s21::S21Vector<int> s21_vector = {1, 2, 3};
  s21_vector.insert_many_back(4);
  std::vector<int> std_vector = {1, 2, 3};
  std_vector.emplace_back(4);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}

TEST(VectorTest, insert_many_back_1) {
  s21::S21Vector<int> s21_vector = {1, 2, 3};
  s21_vector.insert_many_back(4, 5, 6);
  std::vector<int> std_vector = {1, 2, 3, 4, 5, 6};

  auto i = 0;
  for (auto it = std_vector.begin(); it != std_vector.end(); it++) {
    EXPECT_EQ(s21_vector.at(i), *it);
    i++;
  }
}