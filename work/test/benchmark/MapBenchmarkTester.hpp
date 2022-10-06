#ifndef MAPBENCHMARKTESTER_HPP
#define MAPBENCHMARKTESTER_HPP

#if USE_STL
#define NAMESPACE std
#include <map>
#else
#define NAMESPACE ft
#include "map.hpp"
#endif

#include <deque>
#include <string>

#include "Timer.hpp"
#include "print.hpp"
#include "random.hpp"

template < typename Key, typename T >
class MapBenchmarkTester {
 public:
  typedef Key key_t;
  typedef NAMESPACE::pair< Key, T > pair_t;
  typedef NAMESPACE::map< Key, T > map_t;
  typedef typename map_t::iterator iter_t;
  typedef typename map_t::const_iterator citer_t;
  typedef typename std::deque< pair_t > deque_t;
  typedef typename deque_t::iterator deque_iter;

  static const int kLoopCount = 100;
  static const int kElemCount = 10000;

  MapBenchmarkTester(deque_t deq1, deque_t deq2)
      : src_deq1_(deq1),
        src_deq2_(deq2),
        original_(deq1.begin(), deq1.end()),
        value_(deq2.front()) {}

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

  void test_default_ctor() { map_t default_vec; }

  void test_range_ctor() { map_t map(src_deq2_.begin(), src_deq2_.end()); }

  void test_copy_ctor() { map_t map(original_); }

  void test_op_assign(map_t& map) { map = original_; }

  void test_get_allocator() { original_.get_allocator(); }

  void test_op_subscript(map_t& map) { map[random_index(map)]; }

  void test_begin() { original_.begin(); }

  void test_end() { original_.end(); }

  void test_rbegin() { original_.rbegin(); }

  void test_rend() { original_.rend(); }

  void test_empty() { original_.empty(); }

  void test_size() { original_.size(); }

  void test_max_size() { original_.max_size(); }

  void test_capacity() { original_.capacity(); }

  void test_clear(map_t& map) { map.clear(); }

  void test_insert_one(map_t& map) { map.insert(value_); }

  void test_insert_hint(map_t& map) { map.insert(random_itr(map), value_); }

  void test_insert_range(map_t& map) {
    deque_iter first = random_itr(src_deq2_);
    deque_iter last = random_itr(src_deq2_, first);
    map.insert(first, last);
  }

  void test_erase_one(map_t& map) { map.erase(random_itr(map)); }

  void test_erase_range(map_t& map) {
    iter_t first = random_itr(map);
    iter_t last = random_itr(map, first);
    map.erase(first, last);
  }

  void test_erase_key(map_t& map) { map.erase(random_key(map)); }

  void test_count() { original_.count(random_key(original_)); }

  void test_find() { original_.find(random_key(original_)); }

  void test_lower_bound() { original_.lower_bound(random_key(original_)); }

  void test_upper_bound() { original_.upper_bound(random_key(original_)); }

  void test_equal_range() { original_.equal_range(random_key(original_)); }

  void test_key_comp() { original_.key_comp(); }

  void test_value_comp() { original_.value_comp(); }

  void test_swap(map_t& map) {
    map_t v;
    map.swap(v);
  }

  void test_std_swap(map_t& map) {
    map_t v;
    std::swap(map, v);
  }

  void test_op_eq(map_t& map) { (void)(original_ == map); }

  void test_op_ne(map_t& map) { (void)(original_ != map); }

  void test_op_lt(map_t& map) { (void)(original_ < map); }

  void test_op_le(map_t& map) { (void)(original_ <= map); }

  void test_op_gt(map_t& map) { (void)(original_ > map); }

  void test_op_ge(map_t& map) { (void)(original_ >= map); }

  void measure(const std::string& func_name,
               void (MapBenchmarkTester::*func)(void)) {
    Timer timer;
    print_func("map " + func_name);
    for (int i = 0; i < kLoopCount; i++) {
      timer.start();
      (this->*func)();
      timer.stop();
    }
    print_time(timer.elapsed_time());
  }

  void measure(const std::string& func_name,
               void (MapBenchmarkTester::*func)(map_t&)) {
    Timer timer;
    print_func("map " + func_name);
    for (int i = 0; i < kLoopCount; i++) {
      map_t map(original_);
      timer.start();
      (this->*func)(map);
      timer.stop();
    }
    print_time(timer.elapsed_time());
  }

 private:
  typename map_t::key_type random_key(const map_t& map) {
    return random_itr(map)->first;
  }

  deque_t src_deq1_;
  deque_t src_deq2_;
  const map_t original_;
  typename map_t::value_type value_;
};

#endif /* MAPBENCHMARKTESTER_HPP */
