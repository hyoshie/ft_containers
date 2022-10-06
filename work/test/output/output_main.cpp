#include <cstdlib>

#include "output_test.hpp"

int main() {
  test_vector();
  test_stack();
  test_pair();
  test_map();
  test_set();

  // if (system("uname | grep Darwin  > /dev/null") == 0) {
  //   system("leaks -q output_ft >&2");
  // }
}
