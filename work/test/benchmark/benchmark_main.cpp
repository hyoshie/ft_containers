#include <cstdlib>
#include <iostream>

#include "benchmark_test.hpp"

int main() {
  srand(time(NULL));
  test_vector();
  test_stack();
  test_map();
  test_set();

  // if (system("uname | grep Darwin  > /dev/null") == 0) {
  //   system("leaks -q benchmark_ft >&2");
  // }
}
