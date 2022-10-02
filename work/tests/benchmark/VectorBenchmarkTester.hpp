#ifndef VECTORBENCHMARKTESTER_HPP
#define VECTORBENCHMARKTESTER_HPP

#if USE_STL
#define ft std
#include <vector>
#else
#include "vector.hpp"
#endif

#include <deque>
#include <iostream>

template < typename T >
class VectorBenchmarkTester {
 public:
  typedef ft::vector< T > test_vec;
  typedef typename test_vec::iterator test_iter;
  typedef typename test_vec::const_iterator test_citer;
  typedef std::deque< T > test_deq;
  typedef typename test_deq::const_iterator test_deq_citer;

  VectorBenchmarkTester(const std::deque< T >& deq) : src_deq_(deq) {
    std::cout << "Create Original Vector" << std::endl;
    for (test_deq_citer it = src_deq_.begin(); it != src_deq_.end(); it++) {
      original_.push_back(*it);
    }
  }

  void run() {
    // test_default_ctor();
    // measure(&VectorBenchmarkTester::print);
    measure("default ctor", &VectorBenchmarkTester::test_default_ctor);
    measure("value ctor", &VectorBenchmarkTester::test_value_ctor);
    measure("range ctor", &VectorBenchmarkTester::test_range_ctor);
    measure("copy ctor", &VectorBenchmarkTester::test_copy_ctor);
    measure("at", &VectorBenchmarkTester::test_at);
    measure("op_subscript", &VectorBenchmarkTester::test_op_subscript);
    measure("front", &VectorBenchmarkTester::test_front);
    measure("back", &VectorBenchmarkTester::test_back);
    ;
    ;
  }

  void test_default_ctor() {
    for (int i = 0; i < kLoopCount; i++) {
      test_vec default_vec;
    }
  }

  void test_value_ctor() {
    for (int i = 0; i < kLoopCount; i++) {
      test_vec vec(kElemCount, src_deq_.front());
    }
  }

  void test_range_ctor() {
    for (int i = 0; i < kLoopCount; i++) {
      test_vec vec(src_deq_.begin(), src_deq_.end());
    }
  }

  void test_copy_ctor() {
    for (int i = 0; i < kLoopCount; i++) {
      test_vec vec(original_);
    }
  }

  void test_at() {
    test_vec vec(original_);
    typename test_vec::size_type index = vec.size() / 2;
    for (int i = 0; i < kLoopCount; i++) {
      vec.at(index);
    }
  }

  void test_op_subscript() {
    test_vec vec(original_);
    typename test_vec::size_type index = vec.size() / 2;
    for (int i = 0; i < kLoopCount; i++) {
      vec[index];
    }
  }

  void test_front() {
    test_vec vec(original_);
    for (int i = 0; i < kLoopCount; i++) {
      vec.front();
    }
  }

  void test_back() {
    test_vec vec(original_);
    for (int i = 0; i < kLoopCount; i++) {
      vec.back();
    }
  }

  void print() {
    std::cerr << "[\x1b[32mPASS\x1b[39m]" << std::endl;
    ;
  }

  void measure(const std::string& name,
               void (VectorBenchmarkTester::*func)(void)) {
    pout(name);
    clock_t start, end;
    start = clock();
    (this->*func)();
    end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << time << std::endl;
  }

 private:
  template < typename U >
  void pout(U s) {
    static int no;
    std::cout << std::endl;
    std::cout << "--- [" << ++no << "]:" << s << " ---" << std::endl;
  }

  static const int kLoopCount = 100000;
  static const int kElemCount = 100;
  test_vec original_;
  const std::deque< T > src_deq_;
};

#endif /* VECTORBENCHMARKTESTER_HPP */
