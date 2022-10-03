#include <cstdlib>
#include <iostream>

#include "benchmark_test.hpp"

int main() {
  srand(time(NULL));
  test_vector();
  test_stack();
  test_map();
}
