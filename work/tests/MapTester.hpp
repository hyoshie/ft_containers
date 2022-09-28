#ifndef MAPTESTER_HPP
#define MAPTESTER_HPP

#if USE_STL
#define ft std
#include <map>
#else
#include "map.hpp"
#endif

#include <functional>
#include <iostream>
#include <vector>

template < typename Key, typename T, typename Compare = std::less< Key > >
class MapTester {
 public:
  // 型
  typedef ft::pair< Key, T > test_pair;
  typedef ft::map< Key, T, Compare > test_map;
  typedef typename test_map::iterator test_iter;
  typedef typename test_map::const_iterator test_citer;
  typedef typename std::vector< test_pair > test_vec;
  typedef typename test_vec::iterator test_vec_iter;

  // メンバ関数
  MapTester(test_vec vec) : vec_(vec), default_size_(vec.size()) {
    std::cout << "Create Original Map" << std::endl;
    for (test_vec_iter it = vec_.begin(); it != vec_.end(); it++) {
      original_.insert(*it);
    }
  }

  void run() {
    test_field();
    test_ctor();
    test_op_assign();
    test_get_allocator();
    ;
  }

  void test_field() {
    pout("field");
    for (test_vec_iter it = vec_.begin(); it != vec_.end(); it++) {
      std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    }
    std::cout << "default_size:" << default_size_ << std::endl;
    print_info(original_);
  }

  void test_default_ctor() {
    pout("default ctor");
    test_map default_map;
    print_info(default_map);
  }

  void test_arg_ctor() {
    pout("arg ctor");
    std::greater< Key > comp;
    std::allocator< test_pair > alloc;
    ft::map< Key, T, std::greater< Key > > arg_map(comp, alloc);
    for (test_vec_iter it = vec_.begin(); it != vec_.end(); it++) {
      arg_map.insert(*it);
    }
    print_info(arg_map);
  }

  void test_range_ctor() {
    pout("range ctor");
    std::greater< Key > comp;
    std::allocator< test_pair > alloc;
    ft::map< Key, T, std::greater< Key > > range_map(vec_.begin(), vec_.end(),
                                                     comp, alloc);
    for (test_vec_iter it = vec_.begin(); it != vec_.end(); it++) {
      range_map.insert(*it);
    }
    print_info(range_map);
  }

  void test_copy_ctor() {
    pout("copy ctor");
    test_map copy(original_);
    print_info(copy);
  }

  void test_get_allocator() {
    pout("get_allocator");
    std::allocator< T > alloc;
    std::cout << std::boolalpha << (alloc == original_.get_allocator())
              << std::endl;
  }

  void test_ctor() {
    pout("ctor");
    test_default_ctor();
    test_arg_ctor();
    test_range_ctor();
    test_copy_ctor();
  }

  void test_op_assign() {
    pout("op_assign");
    test_map map;
    map.insert(*vec_.begin());
    map = original_;
    print_info(map);
  }

 private:
  template < typename U >
  void pout(U s) {
    static int no;
    std::cout << std::endl;
    std::cout << "--- [" << ++no << "]:" << s << " ---" << std::endl;
  }

  template < typename Map >
  void print_info(const Map& map) {
    for (test_citer it = map.begin(); it != map.end(); it++) {
      std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    }
    std::cout << "size:" << map.size() << std::endl;
  }

  test_vec vec_;
  size_t default_size_;
  test_map original_;
};

#endif
