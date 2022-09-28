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

  void test_ctor() {
    pout("ctor");
    test_map default_map;
    std::greater< Key > comp;
    std::allocator< test_pair > alloc;
    ft::map< Key, T, std::greater< Key > > map(comp, alloc);
    print_info(default_map);
    for (test_vec_iter it = vec_.begin(); it != vec_.end(); it++) {
      map.insert(*it);
    }
    print_info(map);

    ft::map< Key, T, std::greater< Key > > iter_map(vec_.begin(), vec_.end(),
                                                    comp, alloc);
    print_info(iter_map);
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
