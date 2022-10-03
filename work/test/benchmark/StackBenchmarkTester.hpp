#ifndef STACKBENCHMARKTESTER
#define STACKBENCHMARKTESTER

#if USE_STL
#define test_namespace std
#include <stack>
#else
#define test_namespace ft
#include "stack.hpp"
#endif

#include <iomanip>
#include <iostream>

template < typename T, typename Container >
class StackBenchmarkTester {
 public:
  typedef test_namespace::stack< T, Container > test_stack;
  typedef Container test_con;
  typedef typename test_con::const_iterator test_con_citer;

  static const int kLoopCount = 1000;
  static const int kElemCount = 50;

  StackBenchmarkTester(const Container& c) : src_(c) {
    for (test_con_citer it = src_.begin(); it != src_.end(); it++) {
      original_.push(*it);
    }
  }

  void run() {
    measure("def_ctor", &StackBenchmarkTester::test_default_ctor);
    measure("arg_ctor", &StackBenchmarkTester::test_arg_ctor);
    measure("copy_ctor", &StackBenchmarkTester::test_copy_ctor);
    measure("op_assign", &StackBenchmarkTester::test_op_assign);
    measure("top", &StackBenchmarkTester::test_top);
    measure("empty", &StackBenchmarkTester::test_empty);
    measure("size", &StackBenchmarkTester::test_size);
    measure("push", &StackBenchmarkTester::test_push);
    measure("pop", &StackBenchmarkTester::test_pop);
    measure("op_compare", &StackBenchmarkTester::test_op_compare);
  }

  void test_default_ctor() {
    for (int i = 0; i < kLoopCount; i++) {
      test_stack default_stack;
    }
  }

  void test_arg_ctor() {
    for (int i = 0; i < kLoopCount; i++) {
      test_stack default_stack(src_);
    }
  }

  void test_copy_ctor() {
    for (int i = 0; i < kLoopCount; i++) {
      test_stack stack(original_);
    }
  }

  void test_op_assign() {
    typename test_stack::value_type val1 = src_[0];
    test_stack stack1(original_);
    test_stack stack2;
    stack2.push(val1);
    for (int i = 0; i < kLoopCount; i++) {
      stack1 = stack2;
      stack2 = original_;
    }
  }

  void test_top() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.top();
    }
  }

  void test_empty() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.empty();
    }
  }

  void test_size() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.size();
    }
  }

  void test_push() {
    typename test_stack::value_type val1 = src_[0];
    for (int i = 0; i < kLoopCount; i++) {
      original_.push(val1);
    }
  }

  void test_pop() {
    for (int i = 0; i < kElemCount; i++) {
      original_.pop();
    }
  }

  void test_op_compare() {
    test_stack stack(original_);
    typename test_stack::value_type val1 = src_[0];
    stack.push(val1);
    for (int i = 0; i < kLoopCount; i++) {
      original_ == stack;
      original_ != stack;
      original_ < stack;
      original_ <= stack;
      original_ > stack;
      original_ >= stack;
    }
  }

  void measure(const std::string& name,
               void (StackBenchmarkTester::*func)(void)) {
    pout(name);
    clock_t start, end;
    start = clock();
    (this->*func)();
    end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << std::fixed << time << std::endl;
  }

 private:
  template < typename U >
  void pout(U s) {
    std::cout << std::setw(13) << std::left << s << ": ";
  }

  test_stack original_;
  const Container src_;
};

#endif /* STACKBENCHMARKTESTER */
