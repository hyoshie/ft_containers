#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

// int main() {
//   // std::vector<int> v(100, 123);
//   // std::vector<int> v(100);
//   std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};
//   v.reserve(3);
//   v.reserve(100);
//   std::cout << std::boolalpha << "size  :" << v.size() << std::endl
//             << "cap   :" << v.capacity() << std::endl
//             << "empty :" << v.empty() << std::endl
//             << "[5]   :" << v[5] << std::endl;
// }
struct X {
  X() { std::cout << "default constructed.\n"; }
  ~X() { std::cout << "dst.\n"; }
};

int main() {
  auto print = [](auto x) { std::cerr << x << std::endl; };
  // std::vector<int> v(5, 42);
  std::array<int, 5> a{1, 2, 3, 4, 5};
  std::vector<int> v(std::begin(a), std::end(a));
  std::for_each(v.begin(), v.end(), print);
}
