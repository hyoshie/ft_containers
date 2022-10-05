#ifndef STACKBENCHMARKTESTER
#define STACKBENCHMARKTESTER

#if USE_STL
#define NAMESPACE std
#include <stack>
#else
#define NAMESPACE ft
#include "stack.hpp"
#endif

#include <string>

#include "Timer.hpp"
#include "print.hpp"

template < typename T, typename Container >
class StackBenchmarkTester {
 public:
  typedef NAMESPACE::stack< T, Container > test_stack;
  typedef Container test_con;
  typedef typename test_con::const_iterator test_con_citer;

  static const int kLoopCount = 100;
  static const int kElemCount = 1000;

  StackBenchmarkTester(const Container& c)
      : src_(c), original_(create_stack()), value_(original_.top()) {}

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
    measure("op_eq", &StackBenchmarkTester::test_op_eq);
    measure("op_ne", &StackBenchmarkTester::test_op_ne);
    measure("op_lt", &StackBenchmarkTester::test_op_lt);
    measure("op_le", &StackBenchmarkTester::test_op_le);
    measure("op_gt", &StackBenchmarkTester::test_op_gt);
    measure("op_ge", &StackBenchmarkTester::test_op_ge);
  }

  void test_default_ctor() { test_stack default_stack; }

  void test_arg_ctor() { test_stack default_stack(src_); }

  void test_copy_ctor() { test_stack stack(original_); }

  void test_op_assign(test_stack& stack) { stack = original_; }

  void test_top() { original_.top(); }

  void test_empty() { original_.empty(); }

  void test_size() { original_.size(); }

  void test_push(test_stack& stack) { stack.push(value_); }

  void test_pop(test_stack& stack) { stack.pop(); }

  void test_op_eq(test_stack& stack) { (void)(original_ == stack); }

  void test_op_ne(test_stack& stack) { (void)(original_ != stack); }

  void test_op_lt(test_stack& stack) { (void)(original_ < stack); }

  void test_op_le(test_stack& stack) { (void)(original_ <= stack); }

  void test_op_gt(test_stack& stack) { (void)(original_ > stack); }

  void test_op_ge(test_stack& stack) { (void)(original_ >= stack); }

  void measure(const std::string& func_name,
               void (StackBenchmarkTester::*func)(void)) {
    Timer timer;
    print_func(func_name);
    for (int i = 0; i < kLoopCount; i++) {
      timer.start();
      (this->*func)();
      timer.stop();
    }
    print_time(timer.elapsed_time());
    timer.reset();
  }

  void measure(const std::string& func_name,
               void (StackBenchmarkTester::*func)(test_stack&)) {
    Timer timer;
    print_func(func_name);
    for (int i = 0; i < kLoopCount; i++) {
      test_stack stack(original_);
      stack.pop();
      timer.start();
      (this->*func)(stack);
      timer.stop();
    }
    print_time(timer.elapsed_time());
    timer.reset();
  }

 private:
  test_stack create_stack() {
    test_stack stack;
    for (test_con_citer it = src_.begin(); it != src_.end(); it++) {
      stack.push(*it);
    }
    return stack;
  }

  const Container src_;
  const test_stack original_;
  typename test_stack::value_type value_;
};

#endif /* STACKBENCHMARKTESTER */
