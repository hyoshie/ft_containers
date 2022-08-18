#include <array>
#include <iostream>
#include <mymacro>

void printIter() {
  std::array<int, 5> a = {1, 2, 3, 4, 5};
  auto first = std::begin(a);
  auto last = std::end(a);
  PRINT(*first);
  auto iter = a.begin();
  PRINT(*iter);
  ++iter;
  PRINT(*iter);
}

void useIndirectionOperator() {
  std::array<int, 5> a = {1, 2, 3, 4, 5};
  auto iter = a.begin();
  int x = *iter;
  *iter = 0;
  PRINT(x);
  PRINT(*iter);
}

int main() {
  // printIter();
  useIndirectionOperator();
  ;
}
