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
  typedef Key test_key;
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
    test_swap();
    test_count();
    test_find();
    test_equal_range();
    test_lower_bound();
    test_upper_bound();
    test_key_comp();
    test_value_comp();
    test_op_compare();
    // 木を表示
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

  void test_swap() {
    pout("swap");
    test_map map(original_);
    test_map added(original_);
    added.insert(new_pair_);

    //メソッド
    map.swap(added);
    print_info(map);
    print_info(added);

    //非メソッド
    std::swap(map, added);
    print_info(map);
    print_info(added);
  }

  void test_count() {
    pout("count");
    const test_map c_map(original_);

    test_citer found = c_map.begin();
    // 1
    std::cout << c_map.count(found->first) << std::endl;
    // 0
    std::cout << c_map.count(new_pair_.first) << std::endl;
  }

  void test_find() {
    pout("find");
    test_map map(original_);
    const test_map c_map(original_);

    // 成功
    test_key key = map.begin()->first;
    test_iter found = map.find(key);
    test_citer c_found = c_map.find(key);

    print_iter(found);
    print_iter(c_found);

    // 失敗
    key = new_pair_.first;
    test_iter not_found = map.find(key);
    test_citer c_not_found = c_map.find(key);

    std::cout << (not_found == map.end()) << std::endl;
    std::cout << (c_not_found == c_map.end()) << std::endl;
  }

  void test_equal_range() {
    pout("equal_range");
    test_map map(original_);
    const test_map c_map(original_);

    // 存在するkey
    test_key key = map.begin()->first;
    ft::pair< test_iter, test_iter > pair = map.equal_range(key);
    ft::pair< test_citer, test_citer > c_pair = c_map.equal_range(key);

    print_iter_range(pair.first, pair.second);
    print_iter_range(c_pair.first, c_pair.second);

    // 存在しないkey
    // 1つ目の要素 < key < 2つめの要素なので、2つのイテレータは等しくなる
    key = new_pair_.first;
    std::cout << key << std::endl;
    pair = map.equal_range(key);
    c_pair = c_map.equal_range(key);

    std::cout << (pair.first == pair.second) << std::endl;
    std::cout << (c_pair.first == c_pair.second) << std::endl;
  }

  void test_lower_bound() {
    pout("lower_bound");
    test_map map(original_);
    const test_map c_map(original_);

    // 存在するkey
    test_key key = map.begin()->first;
    test_iter found = map.lower_bound(key);
    test_citer c_found = c_map.lower_bound(key);

    print_iter(found);
    print_iter(c_found);

    // 存在しないkey、範囲内
    key = new_pair_.first;
    found = map.lower_bound(key);
    c_found = c_map.lower_bound(key);

    print_iter(found);
    print_iter(c_found);

    // 存在しないkey、範囲外
    test_iter last = --map.end();

    key = last->first;
    key++;
    test_iter not_found = map.lower_bound(key);
    test_citer c_not_found = c_map.lower_bound(key);

    std::cout << (not_found == map.end()) << std::endl;
    std::cout << (c_not_found == c_map.end()) << std::endl;
  }

  void test_upper_bound() {
    pout("upper_bound");
    test_map map(original_);
    const test_map c_map(original_);

    // 存在するkey
    test_key key = map.begin()->first;
    test_iter found = map.upper_bound(key);
    test_citer c_found = c_map.upper_bound(key);

    print_iter(found);
    print_iter(c_found);

    // 存在しないkey、範囲内
    key = new_pair_.first;
    found = map.upper_bound(key);
    c_found = c_map.upper_bound(key);

    print_iter(found);
    print_iter(c_found);

    // 存在しないkey、範囲外
    test_iter last = --map.end();

    key = last->first;
    key++;
    test_iter not_found = map.upper_bound(key);
    test_citer c_not_found = c_map.upper_bound(key);

    std::cout << (not_found == map.end()) << std::endl;
    std::cout << (c_not_found == c_map.end()) << std::endl;
  }

  void print_graph() {
    pout("get_allocator");
    std::allocator< T > alloc;
    std::cout << std::boolalpha << (alloc == original_.get_allocator())
              << std::endl;
  }

  void test_key_comp() {
    pout("key_comp");
    const test_map c_map(original_);

    Compare comp = c_map.key_comp();
    test_citer it_1st = c_map.begin();
    test_citer it_2nd = ++c_map.begin();
    std::cout << comp(it_1st->first, it_2nd->first) << std::endl;
  }

  void test_value_comp() {
    pout("value_comp");
    const test_map c_map(original_);

    typename test_map::value_compare comp = c_map.value_comp();
    test_citer it_1st = c_map.begin();
    test_citer it_2nd = ++c_map.begin();
    test_pair pair_1st(it_1st->first, it_1st->second);
    test_pair pair_2nd(it_2nd->first, it_2nd->second);
    std::cout << comp(pair_1st, pair_2nd) << std::endl;
  }

  void test_op_compare() {
    pout("op_compare");
    test_map map(original_);
    const test_map c_map(original_);
    map.insert(new_pair_);

    // 同じ。ついでにconstもチェック
    std::cout << (original_ == c_map) << std::endl;
    std::cout << (original_ != c_map) << std::endl;
    std::cout << (original_ < c_map) << std::endl;
    std::cout << (original_ <= c_map) << std::endl;
    std::cout << (original_ > c_map) << std::endl;
    std::cout << (original_ >= c_map) << std::endl;

    // 違う
    std::cout << (original_ == map) << std::endl;
    std::cout << (original_ != map) << std::endl;
    std::cout << (original_ < map) << std::endl;
    std::cout << (original_ <= map) << std::endl;
    std::cout << (original_ > map) << std::endl;
    std::cout << (original_ >= map) << std::endl;
  }

 private:
  template < typename U >
  void pout(U s) {
    static int no;
    std::cout << std::endl;
    std::cout << "--- [" << ++no << "]:" << s << " ---" << std::endl;
  }

  template < typename Map >
  void print_info(Map map) {
    for (test_citer it = map.begin(); it != map.end(); it++) {
      print_pair(*it);
    }
    std::cout << "size:" << map.size() << std::endl;
  }

  template < typename Pair >
  void print_pair(Pair pair) {
    std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
  }

  template < typename Iter >
  void print_iter(Iter iter) {
    std::cout << "(" << iter->first << ", " << iter->second << ")" << std::endl;
  }

  template < typename Iter >
  void print_iter_range(Iter first, Iter last) {
    for (; first != last; first++) {
      print_iter(first);
    }
  }

  test_vec vec1_;
  test_vec vec2_;
  size_t default_size_;
  test_map original_;
  test_pair new_pair_;
};

#endif
