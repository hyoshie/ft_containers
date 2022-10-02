#ifndef VECTORBENCHMARKTESTER_HPP
#define VECTORBENCHMARKTESTER_HPP

#if USE_STL
#define ft std
#include <vector>
#else
#include "vector.hpp"
#endif

#include <deque>
#include <iomanip>
#include <iostream>

template < typename T >
class VectorBenchmarkTester {
 public:
  typedef ft::vector< T > test_vec;
  typedef typename test_vec::iterator test_iter;
  typedef typename test_vec::const_iterator test_citer;
  typedef std::deque< T > test_deq;
  typedef typename test_deq::const_iterator test_deq_citer;

  static const int kLoopCount = 10000;
  static const int kElemCount = 100;

  VectorBenchmarkTester(const std::deque< T >& deq) : src_deq_(deq) {
    for (test_deq_citer it = src_deq_.begin(); it != src_deq_.end(); it++) {
      original_.push_back(*it);
    }
  }

  void run() {
    measure("def_ctor", &VectorBenchmarkTester::test_default_ctor);
    measure("value_ctor", &VectorBenchmarkTester::test_value_ctor);
    measure("range_ctor", &VectorBenchmarkTester::test_range_ctor);
    measure("copy_ctor", &VectorBenchmarkTester::test_copy_ctor);
    measure("at", &VectorBenchmarkTester::test_at);
    measure("op_subscript", &VectorBenchmarkTester::test_op_subscript);
    measure("front", &VectorBenchmarkTester::test_front);
    measure("back", &VectorBenchmarkTester::test_back);
    measure("begin", &VectorBenchmarkTester::test_begin);
    measure("end", &VectorBenchmarkTester::test_end);
    measure("rbegin", &VectorBenchmarkTester::test_rbegin);
    measure("rend", &VectorBenchmarkTester::test_rend);
    measure("empty", &VectorBenchmarkTester::test_empty);
    measure("size", &VectorBenchmarkTester::test_size);
    measure("max_size", &VectorBenchmarkTester::test_max_size);
    measure("reserve", &VectorBenchmarkTester::test_reserve);
    measure("capacity", &VectorBenchmarkTester::test_capacity);
    measure("clear", &VectorBenchmarkTester::test_clear);
    measure("insert_one", &VectorBenchmarkTester::test_insert_one);
    measure("insert_fill", &VectorBenchmarkTester::test_insert_fill);
    measure("insert_range", &VectorBenchmarkTester::test_insert_range);
    measure("erase_one", &VectorBenchmarkTester::test_erase_one);
    measure("erase_range", &VectorBenchmarkTester::test_erase_range);
    measure("push_back", &VectorBenchmarkTester::test_push_back);
    measure("pop_back", &VectorBenchmarkTester::test_pop_back);
    measure("resize", &VectorBenchmarkTester::test_resize);
    measure("swap", &VectorBenchmarkTester::test_swap);
    measure("std::swap", &VectorBenchmarkTester::test_std_swap);
    measure("op_compare", &VectorBenchmarkTester::test_swap);
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
    typename test_vec::size_type index = original_.size() / 2;
    for (int i = 0; i < kLoopCount; i++) {
      original_.at(index);
    }
  }

  void test_op_subscript() {
    typename test_vec::size_type index = original_.size() / 2;
    for (int i = 0; i < kLoopCount; i++) {
      original_[index];
    }
  }

  void test_front() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.front();
    }
  }

  void test_back() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.back();
    }
  }

  void test_begin() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.begin();
    }
  }

  void test_end() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.end();
    }
  }

  void test_rbegin() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.rbegin();
    }
  }

  void test_rend() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.rend();
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

  void test_max_size() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.max_size();
    }
  }

  void test_reserve() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.reserve(kElemCount + i);
    }
  }

  void test_capacity() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.capacity();
    }
  }

  void test_clear() {
    for (int i = 0; i < kLoopCount; i++) {
      test_vec v(kElemCount);
      v.clear();
    }
  }

  void test_insert_one() {
    typename test_vec::value_type val = original_[0];
    for (int i = 0; i < kLoopCount; i++) {
      original_.insert(original_.end(), val);
    }
  }

  void test_insert_fill() {
    typename test_vec::value_type val = original_[0];
    for (int i = 0; i < kLoopCount; i++) {
      original_.insert(original_.end(), 3, val);
    }
  }

  void test_insert_range() {
    test_deq_citer it = src_deq_.begin();
    test_deq_citer ite = src_deq_.begin() + src_deq_.size() / 2;
    for (int i = 0; i < kLoopCount; i++) {
      original_.insert(original_.end(), it, ite);
    }
  }

  void test_erase_one() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.erase(original_.begin());
    }
  }

  void test_erase_range() {
    for (int i = 0; i < kLoopCount; i++) {
      test_iter it = original_.begin();
      test_iter ite = original_.begin() + original_.size() / 2;
      original_.erase(it, ite);
    }
  }

  void test_push_back() {
    typename test_vec::value_type val = original_[0];
    for (int i = 0; i < kLoopCount; i++) {
      original_.push_back(val);
    }
  }

  void test_pop_back() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.pop_back();
    }
  }

  void test_resize() {
    for (int i = 0; i < kLoopCount; i++) {
      original_.resize(kElemCount / 2 + i);
    }
  }

  void test_swap() {
    test_vec v(kElemCount, original_[0]);
    for (int i = 0; i < kLoopCount; i++) {
      original_.swap(v);
    }
  }

  void test_std_swap() {
    test_vec v(kElemCount, original_[0]);
    for (int i = 0; i < kLoopCount; i++) {
      std::swap(original_, v);
    }
  }

  void test_op_compare() {
    test_vec v(kElemCount, original_[0]);
    for (int i = 0; i < kLoopCount; i++) {
      original_ == v;
      original_ != v;
      original_ < v;
      original_ <= v;
      original_ > v;
      original_ >= v;
    }
  }

  void measure(const std::string& name,
               void (VectorBenchmarkTester::*func)(void)) {
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

  test_vec original_;
  const test_deq src_deq_;
};

#endif /* VECTORBENCHMARKTESTER_HPP */
