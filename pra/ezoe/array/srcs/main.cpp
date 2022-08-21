#include <algorithm>
#include <array>
#include <iostream>
#include <mymacro>

#include "array.hpp"
#include "util.hpp"

void useFrontBackSize() {
  using array_type = array<int, 5>;
  array_type a = {1, 2, 3, 4, 5};
  print(a);
  // std::array<int, 5> sa = {1, 2, 3, 4, 5};
  std::cout << std::endl;
  int &f = a.front();
  int &b = a.back();
  int size = a.size();
  std::cout << f << b << size << std::endl;
}

void useXXcrementOperator() {
  using array_type = array<int, 5>;
  array_type a = {1, 2, 3, 4, 5};

  auto iter = a.begin();
  PRINT(*iter);
  PRINT(*++iter);
  PRINT(*iter++);
  PRINT(*iter);
  PRINT(*iter--);
  PRINT(*iter);
}

void useComparsionOperator() {
  using array_type = array<int, 5>;
  array_type a = {1, 2, 3, 4, 5};

  auto it1 = a.begin();
  auto it2 = a.begin();
  bool is_same = (it1 == it2);
  bool is_differnt = (it1 != it2);
  PRINT(is_same);
  PRINT(is_differnt);
  bool is_ge = (it1 >= it2);
  bool is_gt = (++it1 > it2);
  it2 += 2;
  bool is_le = (it1 <= it2);
  bool is_lt = (it1 < it2);
  PRINT(is_ge);
  PRINT(is_gt);
  PRINT(is_le);
  PRINT(is_lt);
}

void useAlgorithm() {
  using array_type = array<int, 5>;
  array_type a = {1, 2, 3, 4, 5};

  std::for_each(std::begin(a), std::end(a), [](auto x) { std::cout << x; });
}

void useAlismeticOperator() {
  using array_type = array<int, 5>;
  array_type a = {1, 2, 3, 4, 5};

  auto it1 = a.begin();
  PRINT(*it1);
  it1 += 2;
  PRINT(*it1);
  PRINT(*(it1 + 2));
  it1 -= 1;
  PRINT(*it1);
  PRINT(*(it1 - 1));
  PRINT(it1[3]);
}

int main() {
  // useFrontBackSize();
  // useXXcrementOperator();
  useComparsionOperator();
  // useAlgorithm();
  // useAlismeticOperator();
}
