#include <iostream>
#include <vector>

int main() {
  // std::vector<int> v(100, 123);
  // std::vector<int> v(100);
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};
  v.resize(2);
  v.clear();
  std::cout << std::boolalpha << v.size() << v.empty() << v[5] << std::endl;
}
