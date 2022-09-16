#ifndef STACKTESTER_HPP
#define STACKTESTER_HPP

#if USE_STL
#define ft std
#include <stack>
#else
#include "stack.hpp"
#endif

#include <iostream>

template < typename T, typename Container >
class StackTester {
 public:
  // StackTester(const Container &c, const T &pushed) : c_(c), pushed_(pushed)
  // {}
  StackTester(const Container& c) : c_(c) {}

  void run() {
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
    ft::stack< T, Container > default_s;
    ft::stack< T, Container > s(c_);
    print_info(default_s);
    print_info(s);
  }

  void test_op_equal() {
    pout("op_equal");
    ft::stack< T, Container > s(c_);
    ft::stack< T, Container > copy;

    copy = s;
    print_info(copy);
  }

  void test_top() {
    pout("top");
    ft::stack< T, Container > s(c_);
    const ft::stack< T, Container > immutable(c_);

    std::cout << s.top() << std::endl;
    std::cout << immutable.top() << std::endl;
  }

  void test_empty() {
    pout("empty");
    ft::stack< T, Container > s(c_);
    const ft::stack< T, Container > immutable(c_);

    std::cout << s.empty() << std::endl;
    std::cout << immutable.empty() << std::endl;
  }

  void test_size() {
    pout("size");
    ft::stack< T, Container > s(c_);
    const ft::stack< T, Container > immutable(c_);

    std::cout << s.size() << std::endl;
    std::cout << immutable.size() << std::endl;
  }

  void test_push() {
    pout("push");
    ft::stack< T, Container > s(c_);
    const ft::stack< T, Container > immutable(c_);

    s.push(42);
    print_info(s);
  }

  void test_pop() {
    pout("pop");
    ft::stack< T, Container > s(c_);

    s.pop();
    print_info(s);
  }
  // void test_op_compare();
  void test_op_compare() {
    pout("op_compare");

    ft::stack< T, Container > s(c_);
    ft::stack< T, Container > copy(c_);
    ft::stack< T, Container > large_s(c_);

    large_s.push(42);
    std::cout << (s == copy) << std::endl;
    std::cout << (s != copy) << std::endl;
    std::cout << (s < large_s) << std::endl;
    std::cout << (s <= large_s) << std::endl;
    std::cout << (s <= copy) << std::endl;
    std::cout << (large_s >= s) << std::endl;
    std::cout << (s >= copy) << std::endl;
  }

 private:
  template < typename U >
  void pout(U s) {
    static int no;
    std::cout << std::endl;
    std::cout << "--- [" << ++no << "]:" << s << " ---" << std::endl;
  }

  template < typename Stack >
  void print_info(Stack& s) {
    std::cout << "size:" << s.size() << std::endl;
    if (s.size()) {
      std::cout << "top:" << s.top() << std::endl;
    }
    std::cout << "{ ";
    if (s.size()) {
      for (; !s.empty(); s.pop()) {
        std::cout << s.top() << " ";
      }
    }
    std::cout << "}" << std::endl;
  }
  Container c_;
  // T pushed_;
};

template < typename T >
class StackDefaultTester {
 public:
  // StackTester(const Container &c, const T &pushed) : c_(c), pushed_(pushed)
  // {}
  StackDefaultTester() {}

  void run() {
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
    ft::stack< T > default_s;
    print_info(default_s);
  }

  void test_op_equal() {
    pout("op_equal");
    ft::stack< T > s;
    ft::stack< T > copy;

    copy = s;
    print_info(copy);
  }

  void test_top() {
    pout("top");
    ft::stack< T > s;
    const ft::stack< T > immutable;
    s.push(42);
    std::cout << s.top() << std::endl;
  }

  void test_empty() {
    pout("empty");
    ft::stack< T > s;
    const ft::stack< T > immutable;

    std::cout << s.empty() << std::endl;
    std::cout << immutable.empty() << std::endl;
  }

  void test_size() {
    pout("size");
    ft::stack< T > s;
    const ft::stack< T > immutable;

    std::cout << s.size() << std::endl;
    std::cout << immutable.size() << std::endl;
  }

  void test_push() {
    pout("push");
    ft::stack< T > s;

    s.push(42);
    print_info(s);
  }

  void test_pop() {
    pout("pop");
    ft::stack< T > s;

    s.push(42);
    s.push(42);
    s.pop();
    print_info(s);
  }

  void test_op_compare() {
    pout("op_compare");

    ft::stack< T > s;
    ft::stack< T > copy(s);
    ft::stack< T > large_s;

    large_s.push(42);
    std::cout << (s == copy) << std::endl;
    std::cout << (s != copy) << std::endl;
    std::cout << (s < large_s) << std::endl;
    std::cout << (s <= large_s) << std::endl;
    std::cout << (s <= copy) << std::endl;
    std::cout << (large_s >= s) << std::endl;
    std::cout << (s >= copy) << std::endl;
  }

 private:
  template < typename U >
  void pout(U s) {
    static int no;
    std::cout << std::endl;
    std::cout << "--- [" << ++no << "]:" << s << " ---" << std::endl;
  }

  template < typename Stack >
  void print_info(Stack& s) {
    std::cout << "size:" << s.size() << std::endl;
    if (s.size()) {
      std::cout << "top:" << s.top() << std::endl;
    }
    std::cout << "{ ";
    if (s.size()) {
      for (; !s.empty(); s.pop()) {
        std::cout << s.top() << " ";
      }
    }
    std::cout << "}" << std::endl;
  }
  // T pushed_;
};

#endif
