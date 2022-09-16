#include "StackTester.hpp"

#if USE_STL
#define ft std
#include <vector>
#endif

#include <deque>
#include <list>

void test_stack() {
  ft::vector< long > l_vector;
  for (int i = 0; i < 10; i++) {
    l_vector.push_back(i);
  }
  std::deque< long > l_deque;
  for (int i = 0; i < 10; i++) {
    l_deque.push_back(i);
  }
  std::list< long > l_list;
  for (int i = 0; i < 10; i++) {
    l_list.push_back(i);
  }

  StackTester< long, ft::vector< long > > vec_tester(l_vector);
  StackTester< long, std::deque< long > > deq_tester(l_deque);
  StackTester< long, std::list< long > > list_tester(l_list);

  std::cout << std::endl
            << "----- "
            << "stack(from vector)"
            << " -----" << std::endl;
  vec_tester.run();
  std::cout << std::endl
            << "----- "
            << "stack(from deque)"
            << " -----" << std::endl;
  deq_tester.run();
  std::cout << std::endl
            << "----- "
            << "stack(from list)"
            << " -----" << std::endl;
  list_tester.run();
}
