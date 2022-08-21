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
}

void useAlgorithm() {
  using array_type = array<int, 5>;
  array_type a = {1, 2, 3, 4, 5};

  std::for_each(std::begin(a), std::end(a), [](auto x) { std::cout << x; });
}

int main() {
  // useFrontBackSize();
  // useXXcrementOperator();
  // useComparsionOperator();
  useAlgorithm();
}
