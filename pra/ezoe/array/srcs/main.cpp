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

void useIterator() {
  using array_type = array<int, 5>;
  array_type a = {1, 2, 3, 4, 5};

  auto iter = a.begin();
  PRINT(*iter);
  ++iter;
  PRINT(*iter);
}

int main() {
  useFrontBackSize();
  // useIterator();
}
