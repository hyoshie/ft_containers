#ifndef RANDOM_CPP
#define RANDOM_CPP

#include <cstdlib>

size_t random_mini() {
  size_t size = rand() % 50;
  return (size == 0) ? 1 : size;
}

#endif /* RANDOM_CPP */
