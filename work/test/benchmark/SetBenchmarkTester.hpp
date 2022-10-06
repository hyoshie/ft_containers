#ifndef SETBENCHMARKTESTER_HPP
#define SETBENCHMARKTESTER_HPP

#if USE_STL
#define NAMSPACE std
#include <set>
#else
#define NAMSPACE ft
#include "set.hpp"
#endif

#include <deque>
#include <string>

#include "Timer.hpp"
#include "print.hpp"
#include "random.hpp"

template < typename Key >
class SetBenchmarkTester {
 public:
  typedef Key key_t;
  typedef NAMSPACE::set< Key > set_t;
  typedef typename set_t::iterator iter_t;
  typedef typename set_t::const_iterator citer_t;
  typedef typename std::deque< Key > deque_t;
  typedef typename deque_t::iterator deque_iter;

  static const int kLoopCount = 100;
  static const int kElemCount = 1000;

  SetBenchmarkTester(deque_t deq1, deque_t deq2)
      : src_deq1_(deq1),
        src_deq2_(deq2),
        original_(deq1.begin(), deq1.end()),
        value_(deq2.front()) {}

  void run() {
    measure("def_ctor", &SetBenchmarkTester::test_default_ctor);
    measure("range_ctor", &SetBenchmarkTester::test_range_ctor);
    measure("copy_ctor", &SetBenchmarkTester::test_copy_ctor);
    measure("op_assign", &SetBenchmarkTester::test_op_assign);
    measure("begin", &SetBenchmarkTester::test_begin);
    measure("end", &SetBenchmarkTester::test_end);
    measure("rbegin", &SetBenchmarkTester::test_rbegin);
    measure("rend", &SetBenchmarkTester::test_rend);
    measure("empty", &SetBenchmarkTester::test_empty);
    measure("size", &SetBenchmarkTester::test_size);
    measure("max_size", &SetBenchmarkTester::test_max_size);
    measure("clear", &SetBenchmarkTester::test_clear);
    measure("insert_one", &SetBenchmarkTester::test_insert_one);
    measure("insert_fill", &SetBenchmarkTester::test_insert_hint);
    measure("insert_range", &SetBenchmarkTester::test_insert_range);
    measure("erase_one", &SetBenchmarkTester::test_erase_one);
    measure("erase_range", &SetBenchmarkTester::test_erase_range);
    measure("erase_key", &SetBenchmarkTester::test_erase_key);
    measure("count", &SetBenchmarkTester::test_count);
    measure("find", &SetBenchmarkTester::test_find);
    measure("lower_bound", &SetBenchmarkTester::test_lower_bound);
    measure("upper_bound", &SetBenchmarkTester::test_upper_bound);
    measure("equal_range", &SetBenchmarkTester::test_equal_range);
    measure("key_comp", &SetBenchmarkTester::test_key_comp);
    measure("value_comp", &SetBenchmarkTester::test_value_comp);
    measure("swap", &SetBenchmarkTester::test_swap);
    measure("std::swap", &SetBenchmarkTester::test_std_swap);
    measure("op_eq", &SetBenchmarkTester::test_op_eq);
    measure("op_ne", &SetBenchmarkTester::test_op_ne);
    measure("op_lt", &SetBenchmarkTester::test_op_lt);
    measure("op_le", &SetBenchmarkTester::test_op_le);
    measure("op_gt", &SetBenchmarkTester::test_op_gt);
    measure("op_ge", &SetBenchmarkTester::test_op_ge);
  }

  void test_default_ctor() { set_t default_vec; }

  void test_range_ctor() { set_t set(src_deq2_.begin(), src_deq2_.end()); }

  void test_copy_ctor() { set_t set(original_); }

  void test_op_assign(set_t& set) { set = original_; }

  void test_get_allocator() { original_.get_allocator(); }

  void test_begin() { original_.begin(); }

  void test_end() { original_.end(); }

  void test_rbegin() { original_.rbegin(); }

  void test_rend() { original_.rend(); }

  void test_empty() { original_.empty(); }

  void test_size() { original_.size(); }

  void test_max_size() { original_.max_size(); }

  void test_capacity() { original_.capacity(); }

  void test_clear(set_t& set) { set.clear(); }

  void test_insert_one(set_t& set) { set.insert(value_); }

  void test_insert_hint(set_t& set) { set.insert(random_itr(set), value_); }

  void test_insert_range(set_t& set) {
    deque_iter first = random_itr(src_deq2_);
    deque_iter last = random_itr(src_deq2_, first);
    set.insert(first, last);
  }

  void test_erase_one(set_t& set) { set.erase(random_itr(set)); }

  void test_erase_range(set_t& set) {
    iter_t first = random_itr(set);
    iter_t last = random_itr(set, first);
    set.erase(first, last);
  }

  void test_erase_key(set_t& set) { set.erase(random_key(set)); }

  void test_count() { original_.count(random_key(original_)); }

  void test_find() { original_.find(random_key(original_)); }

  void test_lower_bound() { original_.lower_bound(random_key(original_)); }

  void test_upper_bound() { original_.upper_bound(random_key(original_)); }

  void test_equal_range() { original_.equal_range(random_key(original_)); }

  void test_key_comp() { original_.key_comp(); }

  void test_value_comp() { original_.value_comp(); }

  void test_swap(set_t& set) {
    set_t v;
    set.swap(v);
  }

  void test_std_swap(set_t& set) {
    set_t v;
    std::swap(set, v);
  }

  void test_op_eq(set_t& set) { (void)(original_ == set); }

  void test_op_ne(set_t& set) { (void)(original_ != set); }

  void test_op_lt(set_t& set) { (void)(original_ < set); }

  void test_op_le(set_t& set) { (void)(original_ <= set); }

  void test_op_gt(set_t& set) { (void)(original_ > set); }

  void test_op_ge(set_t& set) { (void)(original_ >= set); }

  void measure(const std::string& func_name,
               void (SetBenchmarkTester::*func)(void)) {
    Timer timer;
    print_func("set " + func_name);
    for (int i = 0; i < kLoopCount; i++) {
      timer.start();
      (this->*func)();
      timer.stop();
    }
    print_time(timer.elapsed_time());
  }

  void measure(const std::string& func_name,
               void (SetBenchmarkTester::*func)(set_t&)) {
    Timer timer;
    print_func("set " + func_name);
    for (int i = 0; i < kLoopCount; i++) {
      set_t set(original_);
      timer.start();
      (this->*func)(set);
      timer.stop();
    }
    print_time(timer.elapsed_time());
  }

 private:
  typename set_t::key_type random_key(const set_t& set) {
    return *random_itr(set);
  }

  deque_t src_deq1_;
  deque_t src_deq2_;
  const set_t original_;
  typename set_t::value_type value_;
};

#endif /* SETBENCHMARKTESTER_HPP */
