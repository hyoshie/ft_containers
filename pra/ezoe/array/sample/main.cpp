#include <array>
#include <iostream>
#include <mymacro>

int main() {
  std::array<int, 5> a = {1, 2, 3, 4, 5};
  auto first = std::begin(a);
  auto last = std::end(a);
  PRINT(*first);
  auto iter = a.begin();
  PRINT(*iter);
  ++iter;
  PRINT(*iter);
}
