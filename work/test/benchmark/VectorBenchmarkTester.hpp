#ifndef VECTORBENCHMARKTESTER_HPP
#define VECTORBENCHMARKTESTER_HPP

#if USE_STL
#define ft std
#include <vector>
#else
#include "vector.hpp"
#endif

#include <deque>
#include <string>

#include "Timer.hpp"
#include "print.hpp"
#include "random.hpp"

template < typename T >
class VectorBenchmarkTester {
 public:
  typedef ft::vector< T > test_vec;
  typedef typename test_vec::iterator test_iter;
  typedef typename test_vec::const_iterator test_citer;
  typedef std::deque< T > test_deq;
  typedef typename test_deq::iterator test_deq_iter;
  typedef typename test_deq::const_iterator test_deq_citer;

  static const int kLoopCount = 100;
  static const int kElemCount = 1000;

  VectorBenchmarkTester(const std::deque< T >& deq)
      : src_deq_(deq), original_(deq.begin(), deq.end()) {}

  void run() {
    measure("def_ctor", &VectorBenchmarkTester::test_default_ctor);
    measure("value_ctor", &VectorBenchmarkTester::test_value_ctor);
    measure("range_ctor", &VectorBenchmarkTester::test_range_ctor);
    measure("copy_ctor", &VectorBenchmarkTester::test_copy_ctor);
    measure("op_assign", &VectorBenchmarkTester::test_op_assign);
    measure("assign_fill", &VectorBenchmarkTester::test_assign_fill);
    measure("assign_range", &VectorBenchmarkTester::test_assign_range);
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
    measure("op_eq", &VectorBenchmarkTester::test_op_eq);
    measure("op_ne", &VectorBenchmarkTester::test_op_ne);
    measure("op_lt", &VectorBenchmarkTester::test_op_lt);
    measure("op_le", &VectorBenchmarkTester::test_op_le);
    measure("op_gt", &VectorBenchmarkTester::test_op_gt);
    measure("op_ge", &VectorBenchmarkTester::test_op_ge);
  }

  void test_default_ctor() { test_vec default_vec; }

  void test_value_ctor() { test_vec vec(kElemCount, src_deq_.front()); }

  void test_range_ctor() { test_vec vec(src_deq_.begin(), src_deq_.end()); }

  void test_copy_ctor() { test_vec vec(original_); }

  void test_op_assign(test_vec& vec) { vec = original_; }

  void test_assign_fill(test_vec& vec) { vec.assign(random_size(vec), value_); }

  void test_assign_range(test_vec& vec) {
    test_deq_iter first = random_itr(src_deq_);
    test_deq_iter last = random_itr(src_deq_, first);
    vec.assign(first, last);
  }

  void test_get_allocator() { original_.get_allocator(); }

  void test_at() { original_.at(random_index(original_)); }

  void test_op_subscript(test_vec& vec) { original_[random_index(vec)]; }

  void test_front() { original_.front(); }

  void test_back() { original_.back(); }

  void test_begin() { original_.begin(); }

  void test_end() { original_.end(); }

  void test_rbegin() { original_.rbegin(); }

  void test_rend() { original_.rend(); }

  void test_empty() { original_.empty(); }

  void test_size() { original_.size(); }

  void test_max_size() { original_.max_size(); }

  void test_reserve(test_vec& vec) { vec.reserve(random_size(vec)); }

  void test_capacity() { original_.capacity(); }

  void test_clear(test_vec& vec) { vec.clear(); }

  void test_insert_one(test_vec& vec) { vec.insert(random_itr(vec), value_); }

  void test_insert_fill(test_vec& vec) {
    vec.insert(random_itr(vec), random_mini(), value_);
  }

  void test_insert_range(test_vec& vec) {
    test_deq_iter first = random_itr(src_deq_);
    test_deq_iter last = random_itr(src_deq_, first);
    vec.insert(random_itr(vec), first, last);
  }

  void test_erase_one(test_vec& vec) { vec.erase(random_itr(vec)); }

  void test_erase_range(test_vec& vec) {
    test_iter first = random_itr(vec);
    test_iter last = random_itr(vec, first);
    vec.erase(first, last);
  }

  void test_push_back(test_vec& vec) { vec.push_back(value_); }

  void test_pop_back(test_vec& vec) { vec.pop_back(); }

  void test_resize(test_vec& vec) { vec.resize(random_size(vec)); }

  void test_swap(test_vec& vec) {
    test_vec v;
    vec.swap(v);
  }

  void test_std_swap(test_vec& vec) {
    test_vec v;
    std::swap(vec, v);
  }

  void test_op_eq(test_vec& vec) { original_ == vec; }

  void test_op_ne(test_vec& vec) { original_ != vec; }

  void test_op_lt(test_vec& vec) { original_ < vec; }

  void test_op_le(test_vec& vec) { original_ <= vec; }

  void test_op_gt(test_vec& vec) { original_ > vec; }

  void test_op_ge(test_vec& vec) { original_ >= vec; }

  void measure(const std::string& func_name,
               void (VectorBenchmarkTester::*func)(void)) {
    Timer timer;
    print_func(func_name);
    for (int i = 0; i < kLoopCount; i++) {
      timer.start();
      (this->*func)();
      timer.stop();
    }
    print_time(timer.elapsed_time());
  }

  void measure(const std::string& func_name,
               void (VectorBenchmarkTester::*func)(test_vec&)) {
    Timer timer;
    print_func(func_name);
    for (int i = 0; i < kLoopCount; i++) {
      test_vec vec(original_);
      timer.start();
      (this->*func)(vec);
      timer.stop();
    }
    print_time(timer.elapsed_time());
  }

 private:
  // typename test_vec::size_type random_index(const test_vec& vec) {
  //   return rand() % vec.size();
  // }

  // typename test_vec::size_type random_mini() {
  //   typename test_vec::size_type size = rand() % 50;
  //   return (size == 0) ? 1 : size;
  // }

  // typename test_vec::size_type random_size(const test_vec& vec) {
  //   typename test_vec::size_type size = rand() % vec.size();
  //   return (size == 0) ? 1 : size;
  // }

  test_deq src_deq_;
  const test_vec original_;
  typename test_vec::value_type value_;
};

#endif /* VECTORBENCHMARKTESTER_HPP */
