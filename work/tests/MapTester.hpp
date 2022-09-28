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
  MapTester(test_vec vec1, test_vec vec2, test_pair new_pair)
      : vec1_(vec1),
        vec2_(vec2),
        default_size_(vec1.size()),
        new_pair_(new_pair) {
    std::cout << "Create Original Map" << std::endl;
    for (test_vec_iter it = vec1_.begin(); it != vec1_.end(); it++) {
      original_.insert(*it);
    }
  }

  void run() {
    std::cout << std::boolalpha;
    test_field();
    test_ctor();
    test_op_assign();
    // print_graphを仕込んでいるので一旦コメントアウト
    // test_get_allocator();
    test_op_subscript();
    test_begin_and_end();
    test_rbegin_and_rend();
    test_empty();
    test_size();
    // 環境依存なのでテストしない
    // test_max_size();
    test_clear();
    test_insert();
    test_erase();
    print_graph();
  }

  void test_field() {
    pout("field");
    for (test_vec_iter it = vec1_.begin(); it != vec1_.end(); it++) {
      std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    }
    std::cout << "default_size:" << default_size_ << std::endl;
    std::cout << "new_pair_:";
    print_pair(new_pair_);
    std::cout << std::endl;
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
    for (test_vec_iter it = vec1_.begin(); it != vec1_.end(); it++) {
      arg_map.insert(*it);
    }
    print_info(arg_map);
  }

  void test_range_ctor() {
    pout("range ctor");
    std::greater< Key > comp;
    std::allocator< test_pair > alloc;
    ft::map< Key, T, std::greater< Key > > range_map(vec1_.begin(), vec1_.end(),
                                                     comp, alloc);
    for (test_vec_iter it = vec1_.begin(); it != vec1_.end(); it++) {
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
    map.insert(*vec1_.begin());
    map = original_;
    print_info(map);
  }

  void test_op_subscript() {
    pout("op_subscript");
    test_map map(original_);
    std::cout << map[vec1_.back().first] << std::endl;
    // 見つからないケース
    std::cout << map[new_pair_.first] << std::endl;
    print_info(map);
  }

  void test_begin_and_end() {
    pout("begin and end");
    test_map map(original_);
    const test_map c_map(original_);

    print_pair(*(map.begin()));
    print_pair(*(c_map.begin()));
    print_pair(*--(map.end()));
    print_pair(*--(c_map.end()));
  }

  void test_rbegin_and_rend() {
    pout("begin and end");
    test_map map(original_);
    const test_map c_map(original_);

    print_pair(*(map.rbegin()));
    print_pair(*(c_map.rbegin()));
    print_pair(*--(map.rend()));
    print_pair(*--(c_map.rend()));
  }

  void test_empty() {
    pout("empty");
    const test_map default_map;
    const test_map c_map(original_);

    std::cout << default_map.empty() << std::endl;
    std::cout << c_map.empty() << std::endl;
  }

  void test_size() {
    pout("size");
    const test_map default_map;
    const test_map c_map(original_);

    std::cout << default_map.size() << std::endl;
    std::cout << c_map.size() << std::endl;
  }

  void test_max_size() {
    pout("size");
    const test_map c_map(original_);

    std::cout << c_map.max_size() << std::endl;
  }

  void test_clear() {
    pout("clear");
    test_map map(original_);

    map.clear();
    print_info(map);
  }

  void test_insert1() {
    pout("insert1");
    test_map map(original_);

    // 成功
    ft::pair< test_iter, bool > result = map.insert(new_pair_);
    print_pair(*(result.first));
    std::cout << result.second << std::endl;
    // 失敗
    result = map.insert(new_pair_);
    print_pair(*(result.first));
    std::cout << result.second << std::endl;

    print_info(map);
  }

  void test_insert_hint() {
    pout("insert_hint");
    test_map map(original_);
    test_iter hint = map.begin();

    // 成功
    test_iter result = map.insert(hint, new_pair_);
    print_pair(*result);
    // 失敗
    result = map.insert(hint, new_pair_);
    print_pair(*result);

    print_info(map);
  }

  void test_insert_range() {
    pout("insert_range");
    test_map map(original_);

    map.insert(vec2_.begin(), vec2_.end());
    print_info(map);
  }

  void test_insert() {
    test_insert1();
    test_insert_hint();
    test_insert_range();
  }

  void test_erase_from_iter() {
    pout("erase1");
    test_map map(original_);

    map.erase(map.begin());
    print_info(map);
  }

  void test_erase_from_key() {
    pout("erase_key");
    test_map map(original_);

    test_iter it_2nd = ++map.begin();
    map.erase(it_2nd->first);
    print_info(map);
  }

  void test_erase_range() {
    pout("erase_range");
    test_map map(original_);

    test_iter it_2nd = ++map.begin();
    test_iter it_last = --map.end();
    map.erase(it_2nd, it_last);
    print_info(map);
  }

  void test_erase() {
    test_erase_from_iter();
    test_erase_from_key();
    test_erase_range();
  }

  void print_graph() {
    pout("get_allocator");
    std::allocator< T > alloc;
    std::cout << std::boolalpha << (alloc == original_.get_allocator())
              << std::endl;
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
      print_pair(*it);
    }
    std::cout << "size:" << map.size() << std::endl;
  }

  template < typename Pair >
  void print_pair(const Pair& pair) {
    std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
  }

  test_vec vec1_;
  test_vec vec2_;
  size_t default_size_;
  test_map original_;
  test_pair new_pair_;
};

#endif
