#include <algorithm>
#include <iostream>

#include "vector.hpp"

struct X {
  X() { std::cout << "default constructed.\n"; }
  ~X() { std::cout << "default destructed.\n"; }
};

int main() {
  auto print = [](auto x) { std::cerr << x << std::endl; };
  std::allocator<int> alloc;
  ft::vector<int> v1(10, 1);
  v1[2] = 5;
  v1.resize(5);
  std::for_each(v1.begin(), v1.end(), print);
}
