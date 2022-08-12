#include <array>
#include <iostream>

#include "array.hpp"
#include "util.hpp"

int main() {
  using array_type = array<int, 5>;
  array_type a = {1, 2, 3, 4, 5};
  print(a);
  // std::array<int, 5> sa = {1, 2, 3, 4, 5};
  std::cout << std::endl;
  int &f = a.front();
  int &b = a.back();
  std::cout << f << b << std::endl;
}
