#ifndef STACKTESTER_HPP
#define STACKTESTER_HPP

#if USE_STL
#define NAMESPACE std
#include <stack>
#else
#define NAMESPACE ft
#include "stack.hpp"
#endif

#include <iostream>

template < typename Container >
class StackTester {
 private:
  typedef typename Container::value_type value_t;
  typedef NAMESPACE::stack< value_t, Container > stack_t;

 public:
  static const int kElemCount = 1000;

  StackTester(const Container& c)
      : c_(c), original_(stack_t(c_)), value_(c_.front()) {}

  void run() {
    std::cout << std::boolalpha;
    test_ctor();
    test_op_equal();
    test_top();
    test_empty();
    test_size();
    test_push();
    test_pop();
    // 非メンバ関数
    test_op_compare();
  }

  void test_ctor() {
    pout("ctor");
    stack_t default_s;
    stack_t stack(c_);
    stack_t copy(original_);

    print_info(default_s);
    print_info(stack);
    print_info(copy);
  }

  void test_op_equal() {
    pout("op_equal");
    stack_t copy;

    copy = original_;
    print_info(copy);
  }

  void test_top() {
    pout("top");

    std::cout << original_.top() << std::endl;
  }

  void test_empty() {
    pout("empty");
    stack_t default_s;

    std::cout << default_s.empty() << std::endl;
    std::cout << original_.empty() << std::endl;
  }

  void test_size() {
    pout("size");

    std::cout << original_.size() << std::endl;
  }

  void test_push() {
    pout("push");
    stack_t stack(original_);

    stack.push(value_);
    print_info(stack);
  }

  void test_pop() {
    pout("pop");
    stack_t stack(original_);

    stack.pop();
    print_info(stack);
  }

  void test_op_compare() {
    pout("op_compare");

    stack_t stack(original_);
    stack_t copy(stack);
    stack_t large(stack);
    large.push(value_);

    // 同じ
    std::cout << (stack == copy) << std::endl;
    std::cout << (stack != copy) << std::endl;
    std::cout << (stack < copy) << std::endl;
    std::cout << (stack <= copy) << std::endl;
    std::cout << (stack > copy) << std::endl;
    std::cout << (stack >= copy) << std::endl;

    // 違う
    std::cout << (stack == large) << std::endl;
    std::cout << (stack != large) << std::endl;
    std::cout << (stack < large) << std::endl;
    std::cout << (stack <= large) << std::endl;
    std::cout << (stack > large) << std::endl;
    std::cout << (stack >= large) << std::endl;

    // constとの比較
    std::cout << (stack == original_) << std::endl;
    std::cout << (stack != original_) << std::endl;
    std::cout << (stack < original_) << std::endl;
    std::cout << (stack <= original_) << std::endl;
    std::cout << (stack > original_) << std::endl;
    std::cout << (stack >= original_) << std::endl;
  }

 private:
  template < typename U >
  void pout(U stack) {
    static int no;
    std::cout << std::endl;
    std::cout << "--- [" << ++no << "]:" << stack << " ---" << std::endl;
  }

  template < typename Stack >
  void print_info(Stack& stack) {
    std::cout << "size:" << stack.size() << std::endl;
    if (stack.size()) {
      std::cout << "top:" << stack.top() << std::endl;
    }
    std::cout << "{ ";
    if (stack.size()) {
      for (; !stack.empty(); stack.pop()) {
        std::cout << stack.top() << " ";
      }
    }
    std::cout << "}" << std::endl;
  }

  Container c_;
  const stack_t original_;
  value_t value_;
};

#endif
