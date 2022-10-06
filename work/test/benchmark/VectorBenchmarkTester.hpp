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
  typedef ft::vector< T > vector_t;
  typedef typename vector_t::iterator iter_t;
  typedef typename vector_t::const_iterator citer_t;
  typedef std::deque< T > deque_t;
  typedef typename deque_t::iterator deque_iter;

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

  void test_default_ctor() { vector_t default_vec; }

  void test_value_ctor() { vector_t vec(kElemCount, src_deq_.front()); }

  void test_range_ctor() { vector_t vec(src_deq_.begin(), src_deq_.end()); }

  void test_copy_ctor() { vector_t vec(original_); }

  void test_op_assign() {
    vector_t vec(random_size(original_));
    vec = original_;
  }

  void test_assign_fill(vector_t& vec) { vec.assign(random_size(vec), value_); }

  void test_assign_range(vector_t& vec) {
    deque_iter first = random_itr(src_deq_);
    deque_iter last = random_itr(src_deq_, first);
    vec.assign(first, last);
  }

  void test_get_allocator() { original_.get_allocator(); }

  void test_at() { original_.at(random_index(original_)); }

  void test_op_subscript(vector_t& vec) { original_[random_index(vec)]; }

  void test_front() { original_.front(); }

  void test_back() { original_.back(); }

  void test_begin() { original_.begin(); }

  void test_end() { original_.end(); }

  void test_rbegin() { original_.rbegin(); }

  void test_rend() { original_.rend(); }

  void test_empty() { original_.empty(); }

  void test_size() { original_.size(); }

  void test_max_size() { original_.max_size(); }

  void test_reserve(vector_t& vec) { vec.reserve(random_size(vec)); }

  void test_capacity() { original_.capacity(); }

  void test_clear(vector_t& vec) { vec.clear(); }

  void test_insert_one(vector_t& vec) { vec.insert(random_itr(vec), value_); }

  void test_insert_fill(vector_t& vec) {
    vec.insert(random_itr(vec), random_mini(), value_);
  }

  void test_insert_range(vector_t& vec) {
    deque_iter first = random_itr(src_deq_);
    deque_iter last = random_itr(src_deq_, first);
    vec.insert(random_itr(vec), first, last);
  }

  void test_erase_one(vector_t& vec) { vec.erase(random_itr(vec)); }

  void test_erase_range(vector_t& vec) {
    iter_t first = random_itr(vec);
    iter_t last = random_itr(vec, first);
    vec.erase(first, last);
  }

  void test_push_back(vector_t& vec) { vec.push_back(value_); }

  void test_pop_back(vector_t& vec) { vec.pop_back(); }

  void test_resize(vector_t& vec) { vec.resize(random_size(vec)); }

  void test_swap(vector_t& vec) {
    vector_t v;
    vec.swap(v);
  }

  void test_std_swap(vector_t& vec) {
    vector_t v;
    std::swap(vec, v);
  }

  void test_op_eq(vector_t& vec) { (void)(original_ == vec); }

  void test_op_ne(vector_t& vec) { (void)(original_ != vec); }

  void test_op_lt(vector_t& vec) { (void)(original_ < vec); }

  void test_op_le(vector_t& vec) { (void)(original_ <= vec); }

  void test_op_gt(vector_t& vec) { (void)(original_ > vec); }

  void test_op_ge(vector_t& vec) { (void)(original_ >= vec); }

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
               void (VectorBenchmarkTester::*func)(vector_t&)) {
    Timer timer;
    print_func(func_name);
    for (int i = 0; i < kLoopCount; i++) {
      vector_t vec(original_);
      timer.start();
      (this->*func)(vec);
      timer.stop();
    }
    print_time(timer.elapsed_time());
  }

 private:
  // typename vector_t::size_type random_index(const vector_t& vec) {
  //   return rand() % vec.size();
  // }

  // typename vector_t::size_type random_mini() {
  //   typename vector_t::size_type size = rand() % 50;
  //   return (size == 0) ? 1 : size;
  // }

  // typename vector_t::size_type random_size(const vector_t& vec) {
  //   typename vector_t::size_type size = rand() % vec.size();
  //   return (size == 0) ? 1 : size;
  // }

  deque_t src_deq_;
  const vector_t original_;
  typename vector_t::value_type value_;
};

#endif /* VECTORBENCHMARKTESTER_HPP */
