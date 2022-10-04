#include <deque>
#include <list>

#include "Fixed.hpp"
#include "StackTester.hpp"
#include "vector.hpp"

static void print_test_info(const std::string& info) {
  std::cout << std::endl << "----- " << info << " -----" << std::endl;
}

static void test_base_ftvec() {
  print_test_info("stack(from ft::vector)");

  ft::vector< long > l_vector;
  int elem_count = StackTester< ft::vector< long > >::kElemCount;
  for (int i = 0; i < elem_count; i++) {
    l_vector.push_back(i);
  }

  StackTester< ft::vector< long > > vec_tester(l_vector);
  vec_tester.run();
}

static void test_base_stdlist() {
  print_test_info("stack(from std::list)");

  std::list< long > l_list;
  int elem_count = StackTester< std::list< long > >::kElemCount;
  for (int i = 0; i < elem_count; i++) {
    l_list.push_back(i);
  }

  StackTester< std::list< long > > list_tester(l_list);
  list_tester.run();
}

static void test_base_stddeq() {
  print_test_info("stack(from std::deque)");

  std::deque< long > l_deque;
  int elem_count = StackTester< std::deque< long > >::kElemCount;
  for (int i = 0; i < elem_count; i++) {
    l_deque.push_back(i);
  }

  StackTester< std::deque< long > > deq_tester(l_deque);
  deq_tester.run();
}

static void test_fixed() {
  print_test_info("stack(Fixed)");

  std::deque< Fixed > fixed_deque;
  float base = 1.5;
  int elem_count = StackTester< std::deque< Fixed > >::kElemCount;
  for (int i = 0; i < elem_count; i++) {
    fixed_deque.push_back(Fixed(base * i));
  }

  StackTester< std::deque< Fixed > > deq_tester(fixed_deque);
  deq_tester.run();
}

static void test_primitive() {
  test_base_ftvec();
  test_base_stdlist();
  test_base_stddeq();
}

static void test_user_defined() {
  test_fixed();
  ;
}

void test_stack() {
  test_primitive();
  test_user_defined();
}
