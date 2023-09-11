#include <gtest/gtest.h>

#include <queue>

#include "../s21_containers.h"

TEST(QueueTest, DefaultConstructor) {
  s21::S21Queue<int> A;
  EXPECT_EQ(0, A.size());
  EXPECT_EQ(true, A.empty());
}

TEST(QueueTest, ParamConstructor_1) {
  s21::S21Queue<int> A{1};
  EXPECT_EQ(1, A.size());
  EXPECT_EQ(false, A.empty());
}

TEST(QueueTest, ParamConstructor_2) {
  s21::S21Queue<int> A{1, 2};
  EXPECT_EQ(2, A.size());
  EXPECT_EQ(false, A.empty());
}

TEST(QueueTest, Constructor_Initializer_queue) {
  s21::S21Queue<int> s21_queue{1, 2, 3, 4};
  EXPECT_EQ(s21_queue.front(), 1);
  EXPECT_EQ(s21_queue.back(), 4);
  EXPECT_EQ(s21_queue.size(), size_t(4));
  EXPECT_EQ(s21_queue.empty(), false);
}

TEST(QueueTest, Constructor_Copy) {
  s21::S21Queue<char> s21_queue_1{'a', 'b', 'c', 'd'};
  s21::S21Queue<char> s21_queue_2 = s21_queue_1;

  EXPECT_EQ(s21_queue_1.size(), s21_queue_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_1.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_1.size(), s21_queue_2.size());
    s21_queue_1.pop(), s21_queue_2.pop();
  }
}

TEST(QueueTest, Constructor_Move) {
  s21::S21Queue<char> s21_queue_1;
  s21_queue_1.push('a');
  s21_queue_1.push('b');
  std::queue<char> std_queue_1;
  std_queue_1.push('a');
  std_queue_1.push('b');
  s21::S21Queue<char> s21_queue_2 = std::move(s21_queue_1);
  std::queue<char> std_queue_2 = std::move(std_queue_1);

  EXPECT_EQ(s21_queue_2.size(), std_queue_2.size());
  EXPECT_EQ(s21_queue_1.size(), std_queue_1.size());
  EXPECT_EQ(s21_queue_1.empty(), std_queue_1.empty());
}

TEST(QueueTest, Modifier_Push) {
  s21::S21Queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(5);
  s21_queue.push(0);
  std_queue.push(5);
  std_queue.push(0);
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueTest, Modifier_Pop) {
  s21::S21Queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(5);
  s21_queue.push(0);
  std_queue.push(5);
  std_queue.push(0);
  s21_queue.pop();
  s21_queue.pop();
  std_queue.pop();
  std_queue.pop();
  s21_queue.push(15);
  s21_queue.push(10);
  std_queue.push(15);
  std_queue.push(10);
  s21_queue.pop();
  std_queue.pop();
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueTest, Modifier_Swap) {
  s21::S21Queue<int> s21_queue_1{1, 2, 3, 4};
  s21::S21Queue<int> s21_queue_2{5, 5, 5};
  s21::S21Queue<int> s21_queue_3{1, 2, 3, 4};
  s21::S21Queue<int> s21_queue_4{5, 5, 5};

  s21_queue_1.swap(s21_queue_2);

  EXPECT_EQ(s21_queue_1.size(), s21_queue_4.size());
  EXPECT_EQ(s21_queue_2.size(), s21_queue_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_3.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(s21_queue_1.front(), s21_queue_4.front());
    EXPECT_EQ(s21_queue_1.size(), s21_queue_4.size());
    s21_queue_1.pop(), s21_queue_4.pop();
  }
}

TEST(QueueTest, insert_many_back) {
  s21::S21Queue<int> a;
  a.push(1);
  a.push(2);
  a.push(3);
  a.insert_many_back(1, 1, 2, 5, 6);
  auto it = a.size();
  EXPECT_EQ(8, it);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 6);
}