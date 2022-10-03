#ifndef MAPBENCHMARKTESTER_HPP
#define MAPBENCHMARKTESTER_HPP

#if USE_STL
#define ft std
#include <map>
#else
#include "map.hpp"
#endif

#include <string>
#include <vector>

#include "Timer.hpp"
#include "print.hpp"
#include "random.hpp"

template < typename Key, typename T >
class MapBenchmarkTester {
 public:
  typedef Key test_key;
  typedef ft::pair< Key, T > test_pair;
  typedef ft::map< Key, T > test_map;
  typedef typename test_map::iterator test_iter;
  typedef typename test_map::const_iterator test_citer;
  typedef typename std::vector< test_pair > test_vec;
  typedef typename test_vec::iterator test_vec_iter;

  static const int kLoopCount = 100;
  static const int kElemCount = 1000;

  MapBenchmarkTester(test_vec vec1, test_vec vec2)
      : vec1_(vec1),
        vec2_(vec2),
        original_(vec1.begin(), vec1.end()),
        value_(vec2.front()) {}

  void run() {
    measure("def_ctor", &MapBenchmarkTester::test_default_ctor);
    measure("range_ctor", &MapBenchmarkTester::test_range_ctor);
    measure("copy_ctor", &MapBenchmarkTester::test_copy_ctor);
    measure("op_assign", &MapBenchmarkTester::test_op_assign);
    measure("op_subscript", &MapBenchmarkTester::test_op_subscript);
    measure("begin", &MapBenchmarkTester::test_begin);
    measure("end", &MapBenchmarkTester::test_end);
    measure("rbegin", &MapBenchmarkTester::test_rbegin);
    measure("rend", &MapBenchmarkTester::test_rend);
    measure("empty", &MapBenchmarkTester::test_empty);
    measure("size", &MapBenchmarkTester::test_size);
    measure("max_size", &MapBenchmarkTester::test_max_size);
    measure("clear", &MapBenchmarkTester::test_clear);
    measure("insert_one", &MapBenchmarkTester::test_insert_one);
    measure("insert_fill", &MapBenchmarkTester::test_insert_hint);
    measure("insert_range", &MapBenchmarkTester::test_insert_range);
    measure("erase_one", &MapBenchmarkTester::test_erase_one);
    measure("erase_range", &MapBenchmarkTester::test_erase_range);
    measure("erase_key", &MapBenchmarkTester::test_erase_key);
    measure("count", &MapBenchmarkTester::test_count);
    measure("find", &MapBenchmarkTester::test_find);
    measure("lower_bound", &MapBenchmarkTester::test_lower_bound);
    measure("upper_bound", &MapBenchmarkTester::test_upper_bound);
    measure("equal_range", &MapBenchmarkTester::test_equal_range);
    measure("key_comp", &MapBenchmarkTester::test_key_comp);
    measure("value_comp", &MapBenchmarkTester::test_value_comp);
    measure("swap", &MapBenchmarkTester::test_swap);
    measure("std::swap", &MapBenchmarkTester::test_std_swap);
    measure("op_eq", &MapBenchmarkTester::test_op_eq);
    measure("op_ne", &MapBenchmarkTester::test_op_ne);
    measure("op_lt", &MapBenchmarkTester::test_op_lt);
    measure("op_le", &MapBenchmarkTester::test_op_le);
    measure("op_gt", &MapBenchmarkTester::test_op_gt);
    measure("op_ge", &MapBenchmarkTester::test_op_ge);
  }

  void test_default_ctor() { test_map default_vec; }

  void test_range_ctor() { test_map map(vec2_.begin(), vec2_.end()); }

  void test_copy_ctor() { test_map map(original_); }

  void test_op_assign(test_map& map) { map = original_; }

  void test_get_allocator() { original_.get_allocator(); }

  void test_op_subscript(test_map& map) { map[random_index(map)]; }

  void test_begin() { original_.begin(); }

  void test_end() { original_.end(); }

  void test_rbegin() { original_.rbegin(); }

  void test_rend() { original_.rend(); }

  void test_empty() { original_.empty(); }

  void test_size() { original_.size(); }

  void test_max_size() { original_.max_size(); }

  void test_capacity() { original_.capacity(); }

  void test_clear(test_map& map) { map.clear(); }

  void test_insert_one(test_map& map) { map.insert(value_); }

  void test_insert_hint(test_map& map) { map.insert(random_itr(map), value_); }

  void test_insert_range(test_map& map) {
    test_vec_iter first = random_itr(vec2_);
    test_vec_iter last = random_itr(vec2_, first);
    map.insert(first, last);
  }

  void test_erase_one(test_map& map) { map.erase(random_itr(map)); }

  void test_erase_range(test_map& map) {
    test_iter first = random_itr(map);
    test_iter last = random_itr(map, first);
    map.erase(first, last);
  }

  void test_erase_key(test_map& map) { map.erase(random_key(map)); }

  void test_count() { original_.count(random_key(original_)); }

  void test_find() { original_.find(random_key(original_)); }

  void test_lower_bound() { original_.lower_bound(random_key(original_)); }

  void test_upper_bound() { original_.upper_bound(random_key(original_)); }

  void test_equal_range() { original_.equal_range(random_key(original_)); }

  void test_key_comp() { original_.key_comp(); }

  void test_value_comp() { original_.value_comp(); }

  void test_swap(test_map& map) {
    test_map v;
    map.swap(v);
  }

  void test_std_swap(test_map& map) {
    test_map v;
    std::swap(map, v);
  }

  void test_op_eq(test_map& map) { original_ == map; }

  void test_op_ne(test_map& map) { original_ != map; }

  void test_op_lt(test_map& map) { original_ < map; }

  void test_op_le(test_map& map) { original_ <= map; }

  void test_op_gt(test_map& map) { original_ > map; }

  void test_op_ge(test_map& map) { original_ >= map; }

  void measure(const std::string& func_name,
               void (MapBenchmarkTester::*func)(void)) {
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
               void (MapBenchmarkTester::*func)(test_map&)) {
    Timer timer;
    print_func(func_name);
    for (int i = 0; i < kLoopCount; i++) {
      test_map map(original_);
      timer.start();
      (this->*func)(map);
      timer.stop();
    }
    print_time(timer.elapsed_time());
  }

 private:
  typename test_map::key_type random_key(const test_map& map) {
    return random_itr(map)->first;
  }

  test_vec vec1_;
  test_vec vec2_;
  const test_map original_;
  typename test_map::value_type value_;
};

#endif /* MAPBENCHMARKTESTER_HPP */
