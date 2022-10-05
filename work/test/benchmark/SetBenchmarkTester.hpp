#ifndef SETBENCHMARKTESTER_HPP
#define SETBENCHMARKTESTER_HPP

#if USE_STL
#define ft std
#include <set>
#else
#include "set.hpp"
#endif

#include <string>
#include <vector>

#include "Timer.hpp"
#include "print.hpp"
#include "random.hpp"

template < typename Key >
class SetBenchmarkTester {
 public:
  typedef Key test_key;
  typedef ft::set< Key > test_set;
  typedef typename test_set::iterator test_iter;
  typedef typename test_set::const_iterator test_citer;
  typedef typename std::vector< Key > test_vec;
  typedef typename test_vec::iterator test_vec_iter;

  static const int kLoopCount = 100;
  static const int kElemCount = 1000;

  SetBenchmarkTester(test_vec vec1, test_vec vec2)
      : vec1_(vec1),
        vec2_(vec2),
        original_(vec1.begin(), vec1.end()),
        value_(vec2.front()) {}

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

  void test_default_ctor() { test_set default_vec; }

  void test_range_ctor() { test_set set(vec2_.begin(), vec2_.end()); }

  void test_copy_ctor() { test_set set(original_); }

  void test_op_assign(test_set& set) { set = original_; }

  void test_get_allocator() { original_.get_allocator(); }

  void test_begin() { original_.begin(); }

  void test_end() { original_.end(); }

  void test_rbegin() { original_.rbegin(); }

  void test_rend() { original_.rend(); }

  void test_empty() { original_.empty(); }

  void test_size() { original_.size(); }

  void test_max_size() { original_.max_size(); }

  void test_capacity() { original_.capacity(); }

  void test_clear(test_set& set) { set.clear(); }

  void test_insert_one(test_set& set) { set.insert(value_); }

  void test_insert_hint(test_set& set) { set.insert(random_itr(set), value_); }

  void test_insert_range(test_set& set) {
    test_vec_iter first = random_itr(vec2_);
    test_vec_iter last = random_itr(vec2_, first);
    set.insert(first, last);
  }

  void test_erase_one(test_set& set) { set.erase(random_itr(set)); }

  void test_erase_range(test_set& set) {
    test_iter first = random_itr(set);
    test_iter last = random_itr(set, first);
    set.erase(first, last);
  }

  void test_erase_key(test_set& set) { set.erase(random_key(set)); }

  void test_count() { original_.count(random_key(original_)); }

  void test_find() { original_.find(random_key(original_)); }

  void test_lower_bound() { original_.lower_bound(random_key(original_)); }

  void test_upper_bound() { original_.upper_bound(random_key(original_)); }

  void test_equal_range() { original_.equal_range(random_key(original_)); }

  void test_key_comp() { original_.key_comp(); }

  void test_value_comp() { original_.value_comp(); }

  void test_swap(test_set& set) {
    test_set v;
    set.swap(v);
  }

  void test_std_swap(test_set& set) {
    test_set v;
    std::swap(set, v);
  }

  void test_op_eq(test_set& set) { (void)(original_ == set); }

  void test_op_ne(test_set& set) { (void)(original_ != set); }

  void test_op_lt(test_set& set) { (void)(original_ < set); }

  void test_op_le(test_set& set) { (void)(original_ <= set); }

  void test_op_gt(test_set& set) { (void)(original_ > set); }

  void test_op_ge(test_set& set) { (void)(original_ >= set); }

  void measure(const std::string& func_name,
               void (SetBenchmarkTester::*func)(void)) {
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
               void (SetBenchmarkTester::*func)(test_set&)) {
    Timer timer;
    print_func(func_name);
    for (int i = 0; i < kLoopCount; i++) {
      test_set set(original_);
      timer.start();
      (this->*func)(set);
      timer.stop();
    }
    print_time(timer.elapsed_time());
  }

 private:
  typename test_set::key_type random_key(const test_set& set) {
    return *random_itr(set);
  }

  test_vec vec1_;
  test_vec vec2_;
  const test_set original_;
  typename test_set::value_type value_;
};

#endif /* SETBENCHMARKTESTER_HPP */
