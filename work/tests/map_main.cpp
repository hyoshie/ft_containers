#include <iostream>

#include "MapTester.hpp"

#if USE_STL
#define ft std
#include <map>
#else
#include "map.hpp"
#endif

#include <vector>

void test_map() {
  // ft::pair< char, int > primitive_elements[] = {
  //     ft::make_pair('a', 1),  ft::make_pair('b', 2), ft::make_pair('c', 3),
  //     ft::make_pair('d', 4),  ft::make_pair('e', 5), ft::make_pair('f', 6),
  //     ft::make_pair('g', 7),  ft::make_pair('h', 8), ft::make_pair('i', 9),
  //     ft::make_pair('k', 10),
  // };
  // size_t primitive_size =
  //     sizeof(primitive_elements) / sizeof(primitive_elements[0]);

  std::vector< ft::pair< char, int > > primitives;
  primitives.push_back(ft::make_pair('a', 1));
  primitives.push_back(ft::make_pair('b', 2));
  primitives.push_back(ft::make_pair('c', 3));
  primitives.push_back(ft::make_pair('d', 4));
  primitives.push_back(ft::make_pair('e', 5));
  primitives.push_back(ft::make_pair('f', 6));
  primitives.push_back(ft::make_pair('g', 7));
  primitives.push_back(ft::make_pair('h', 8));
  primitives.push_back(ft::make_pair('i', 9));
  primitives.push_back(ft::make_pair('j', 10));
  // MapTester< char, int > primitive_tester(primitive_elements,
  // primitive_size);
  MapTester< char, int > primitive_tester(primitives);
  primitive_tester.run();
}
