#include <algorithm>
#include <array>
#include <iostream>

#include "vector.hpp"

struct X {
  X() { std::cout << "default constructed.\n"; }
  ~X() { std::cout << "default destructed.\n"; }
};

int main() {
  auto print = [](int x) { std::cerr << x << std::endl; };
  std::allocator<int> alloc;
  std::array<int, 5> a{1, 2, 3, 4, 5};
  ft::vector<int> v(a.begin(), a.end());
  std::for_each(v.begin(), v.end(), print);
  std::cout << v.front() << std::endl;
  std::cout << v.back() << std::endl;
}
