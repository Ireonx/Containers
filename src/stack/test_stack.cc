#include <gtest/gtest.h>

#include <stack>

#include "../s21_containers.h"

TEST(stackTest, DefaultConstructor) {
  s21::S21Stack<int> A;
  EXPECT_EQ(0, A.size());
  EXPECT_EQ(true, A.empty());
}

TEST(stackTest, ParamConstructor_1) {
  s21::S21Stack<int> A{1};
  EXPECT_EQ(1, A.size());
  EXPECT_EQ(false, A.empty());
}

TEST(stackTest, ParamConstructor_2) {
  s21::S21Stack<int> A{1, 2};
  EXPECT_EQ(2, A.size());
  EXPECT_EQ(false, A.empty());
}

TEST(stackTest, Constructor_Default) {
  s21::S21Stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stackTest, Constructor_Initializer_stack) {
  s21::S21Stack<int> s21_stack{1, 2, 3, 4};
  EXPECT_EQ(s21_stack.top(), 4);
  EXPECT_EQ(s21_stack.size(), size_t(4));
  EXPECT_EQ(s21_stack.empty(), false);
}

TEST(stackTest, Constructor_Copy) {
  s21::S21Stack<char> s21_stack_1{'a', 'b', 'c', 'd'};
  s21::S21Stack<char> s21_stack_2(s21_stack_1);

  EXPECT_EQ(s21_stack_1.size(), s21_stack_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_1.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_1.size(), s21_stack_2.size());
    s21_stack_1.pop(), s21_stack_2.pop();
  }
}

TEST(stackTest, Constructor_Move) {
  s21::S21Stack<char> s21_stack_1{'a', 'b', 'c', 'd'};
  s21::S21Stack<char> s21_stack_2 = std::move(s21_stack_1);
  s21::S21Stack<char> s21_stack_3{'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_stack_2.size(), s21_stack_3.size());
  EXPECT_EQ(s21_stack_1.size(), size_t(0));
  EXPECT_EQ(s21_stack_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_3.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_3.size(), s21_stack_2.size());
    s21_stack_3.pop(), s21_stack_2.pop();
  }
}

TEST(stackTest, Modifier_Push) {
  s21::S21Stack<int> s21_stack;
  std::stack<int> std_stack;
  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stackTest, Modifier_Pop) {
  s21::S21Stack<int> s21_stack;
  std::stack<int> std_stack;
  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);
  s21_stack.pop();
  s21_stack.pop();
  std_stack.pop();
  std_stack.pop();
  s21_stack.push(15);
  s21_stack.push(10);
  std_stack.push(15);
  std_stack.push(10);
  s21_stack.pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stackTest, insert_many_front) {
  s21::S21Stack<int> A{1, 2, 3};
  s21::S21Stack<int> B{1, 2, 3, 5, 1, 2, 5, 6};
  A.insert_many_front(5, 1, 2, 5, 6);

  EXPECT_EQ(B.size(), A.size());
  double a, b;
  while (!B.empty()) {
    a = A.top();
    b = B.top();
    EXPECT_EQ(a, b);
    A.pop();
    B.pop();
  }
  EXPECT_EQ(B.size(), A.size());
}

/*TEST(stackTest, Modifier_Swap) {
  s21::S21Stack<std::string> s21_stack_1 {"aboba", "shleppa", "amogus",
                                         "abobus"};
  s21::S21Stack<std::string> s21_stack_2 {"shtirlits", "vovochka", "poruchik"};
  s21::S21Stack<std::string> s21_stack_3 {"aboba", "shleppa", "amogus",
                                         "abobus"};
  s21::S21Stack<std::string> s21_stack_4 {"shtirlits", "vovochka", "poruchik"};

  s21_stack_1.swap(s21_stack_2);

  EXPECT_EQ(s21_stack_1.size(), s21_stack_4.size());
  EXPECT_EQ(s21_stack_2.size(), s21_stack_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_3.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_3.size(), s21_stack_2.size());
    s21_stack_3.pop(), s21_stack_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(s21_stack_1.top(), s21_stack_4.top());
    EXPECT_EQ(s21_stack_1.size(), s21_stack_4.size());
    s21_stack_1.pop(), s21_stack_4.pop();
  }
}*/
