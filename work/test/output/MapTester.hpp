#ifndef MAPTESTER_HPP
#define MAPTESTER_HPP

#if USE_STL
#define NAMESPACE std
#include <map>
#else
#define NAMESPACE ft
#include "map.hpp"
#endif

#include <deque>
#include <functional>
#include <iostream>

#include "IteratorTester.hpp"

template < typename Key, typename T, typename Compare = std::less< Key > >
class MapTester {
 public:
  // 型
  typedef Key key_t;
  typedef NAMESPACE::pair< Key, T > pair_t;
  typedef NAMESPACE::map< Key, T, Compare > map_t;
  typedef typename map_t::iterator iter_t;
  typedef typename map_t::const_iterator citer_t;
  typedef typename std::deque< pair_t > deque_t;
  typedef typename deque_t::iterator deque_iter;

  // メンバ関数
  MapTester(deque_t deq1, deque_t deq2, pair_t new_pair)
      : src_deq1_(deq1),
        src_deq2_(deq2),
        default_size_(deq1.size()),
        new_pair_(new_pair) {
    std::cout << "Create Original Map" << std::endl;
    for (deque_iter it = src_deq1_.begin(); it != src_deq1_.end(); it++) {
      original_.insert(*it);
    }
  }

  void run() {
    std::cout << std::boolalpha;
    test_field();
    test_ctor();
    test_iter();
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
    for (deque_iter it = src_deq1_.begin(); it != src_deq1_.end(); it++) {
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
    map_t default_map;
    print_info(default_map);
  }

  void test_arg_ctor() {
    pout("arg ctor");
    std::greater< Key > comp;
    std::allocator< pair_t > alloc;
    NAMESPACE::map< Key, T, std::greater< Key > > arg_map(comp, alloc);
    for (deque_iter it = src_deq1_.begin(); it != src_deq1_.end(); it++) {
      arg_map.insert(*it);
    }
    print_info(arg_map);
  }

  void test_range_ctor() {
    pout("range ctor");
    std::greater< Key > comp;
    std::allocator< pair_t > alloc;
    NAMESPACE::map< Key, T, std::greater< Key > > range_map(
        src_deq1_.begin(), src_deq1_.end(), comp, alloc);
    for (deque_iter it = src_deq1_.begin(); it != src_deq1_.end(); it++) {
      range_map.insert(*it);
    }
    print_info(range_map);
  }

  void test_copy_ctor() {
    pout("copy ctor");
    map_t copy(original_);
    print_info(copy);
  }

  void test_iter() {
    pout("iter");

    IteratorTester< map_t > tester(original_);
    tester.run();
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
    map_t map;
    map.insert(*src_deq1_.begin());
    map = original_;
    print_info(map);
  }

  void test_op_subscript() {
    pout("op_subscript");
    map_t map(original_);
    std::cout << map[src_deq1_.back().first] << std::endl;
    // 見つからないケース
    std::cout << map[new_pair_.first] << std::endl;
    print_info(map);
  }

  void test_begin_and_end() {
    pout("begin and end");
    map_t map(original_);
    const map_t c_map(original_);

    print_pair(*(map.begin()));
    print_pair(*(c_map.begin()));
    print_pair(*--(map.end()));
    print_pair(*--(c_map.end()));
  }

  void test_rbegin_and_rend() {
    pout("begin and end");
    map_t map(original_);
    const map_t c_map(original_);

    print_pair(*(map.rbegin()));
    print_pair(*(c_map.rbegin()));
    print_pair(*--(map.rend()));
    print_pair(*--(c_map.rend()));
  }

  void test_empty() {
    pout("empty");
    const map_t default_map;
    const map_t c_map(original_);

    std::cout << default_map.empty() << std::endl;
    std::cout << c_map.empty() << std::endl;
  }

  void test_size() {
    pout("size");
    const map_t default_map;
    const map_t c_map(original_);

    std::cout << default_map.size() << std::endl;
    std::cout << c_map.size() << std::endl;
  }

  void test_max_size() {
    pout("size");
    const map_t c_map(original_);

    std::cout << c_map.max_size() << std::endl;
  }

  void test_clear() {
    pout("clear");
    map_t map(original_);

    map.clear();
    print_info(map);
  }

  void test_insert1() {
    pout("insert1");
    map_t map(original_);
    iter_t it = map.begin();

    // 成功
    NAMESPACE::pair< iter_t, bool > result = map.insert(new_pair_);
    print_pair(*(result.first));
    std::cout << result.second << std::endl;
    // 失敗
    result = map.insert(new_pair_);
    print_pair(*(result.first));
    std::cout << result.second << std::endl;

    print_info(map);

    // insert前のiteratorが有効かの確認
    print_iter(it);
  }

  void test_insert_hint() {
    pout("insert_hint");
    map_t map(original_);
    iter_t it = map.begin();
    iter_t hint = map.begin();

    // 成功
    iter_t result = map.insert(hint, new_pair_);
    print_pair(*result);
    // 失敗
    result = map.insert(hint, new_pair_);
    print_pair(*result);

    print_info(map);
    // insert前のiteratorが有効かの確認
    print_iter(it);
  }

  void test_insert_range() {
    pout("insert_range");
    map_t map(original_);
    iter_t it = map.begin();

    map.insert(src_deq2_.begin(), src_deq2_.end());
    print_info(map);
    // insert前のiteratorが有効かの確認
    print_iter(it);
  }

  void test_insert() {
    test_insert1();
    test_insert_hint();
    test_insert_range();
  }

  void test_erase_from_iter() {
    pout("erase1");
    map_t map(original_);
    iter_t it = map.begin();
    iter_t it_2nd = ++map.begin();

    map.erase(it_2nd);
    print_info(map);
    // erase前のiteratorが有効かの確認
    print_iter(it);
  }

  void test_erase_from_key() {
    pout("erase_key");
    map_t map(original_);
    iter_t it = map.begin();
    iter_t it_2nd = ++map.begin();

    map.erase(it_2nd->first);
    print_info(map);
    // erase前のiteratorが有効かの確認
    print_iter(it);
  }

  void test_erase_range() {
    pout("erase_range");
    map_t map(original_);
    iter_t it = map.begin();
    iter_t it_2nd = ++map.begin();
    iter_t it_last = --map.end();

    map.erase(it_2nd, it_last);
    print_info(map);
    // erase前のiteratorが有効かの確認
    print_iter(it);
  }

  void test_erase() {
    test_erase_from_iter();
    test_erase_from_key();
    test_erase_range();
  }

  void test_swap() {
    pout("swap");
    map_t map(original_);
    map_t added(original_);
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
    const map_t c_map(original_);

    citer_t found = c_map.begin();
    // 1
    std::cout << c_map.count(found->first) << std::endl;
    // 0
    std::cout << c_map.count(new_pair_.first) << std::endl;
  }

  void test_find() {
    pout("find");
    map_t map(original_);
    const map_t c_map(original_);

    // 成功
    key_t key = map.begin()->first;
    iter_t found = map.find(key);
    citer_t c_found = c_map.find(key);

    print_iter(found);
    print_iter(c_found);

    // 失敗
    key = new_pair_.first;
    iter_t not_found = map.find(key);
    citer_t c_not_found = c_map.find(key);

    std::cout << (not_found == map.end()) << std::endl;
    std::cout << (c_not_found == c_map.end()) << std::endl;
  }

  void test_equal_range() {
    pout("equal_range");
    map_t map(original_);
    const map_t c_map(original_);

    // 存在するkey
    key_t key = map.begin()->first;
    NAMESPACE::pair< iter_t, iter_t > pair = map.equal_range(key);
    NAMESPACE::pair< citer_t, citer_t > c_pair = c_map.equal_range(key);

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
    map_t map(original_);
    const map_t c_map(original_);

    // 存在するkey
    key_t key = map.begin()->first;
    iter_t found = map.lower_bound(key);
    citer_t c_found = c_map.lower_bound(key);

    print_iter(found);
    print_iter(c_found);

    // 存在しないkey、範囲内
    key = new_pair_.first;
    found = map.lower_bound(key);
    c_found = c_map.lower_bound(key);

    print_iter(found);
    print_iter(c_found);

    // 存在しないkey、範囲外
    iter_t last = --map.end();

    key = last->first;
    key++;
    iter_t not_found = map.lower_bound(key);
    citer_t c_not_found = c_map.lower_bound(key);

    std::cout << (not_found == map.end()) << std::endl;
    std::cout << (c_not_found == c_map.end()) << std::endl;
  }

  void test_upper_bound() {
    pout("upper_bound");
    map_t map(original_);
    const map_t c_map(original_);

    // 存在するkey
    key_t key = map.begin()->first;
    iter_t found = map.upper_bound(key);
    citer_t c_found = c_map.upper_bound(key);

    print_iter(found);
    print_iter(c_found);

    // 存在しないkey、範囲内
    key = new_pair_.first;
    found = map.upper_bound(key);
    c_found = c_map.upper_bound(key);

    print_iter(found);
    print_iter(c_found);

    // 存在しないkey、範囲外
    iter_t last = --map.end();

    key = last->first;
    key++;
    iter_t not_found = map.upper_bound(key);
    citer_t c_not_found = c_map.upper_bound(key);

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
    const map_t c_map(original_);

    Compare comp = c_map.key_comp();
    citer_t it_1st = c_map.begin();
    citer_t it_2nd = ++c_map.begin();
    std::cout << comp(it_1st->first, it_2nd->first) << std::endl;
  }

  void test_value_comp() {
    pout("value_comp");
    const map_t c_map(original_);

    typename map_t::value_compare comp = c_map.value_comp();
    citer_t it_1st = c_map.begin();
    citer_t it_2nd = ++c_map.begin();
    pair_t pair_1st(it_1st->first, it_1st->second);
    pair_t pair_2nd(it_2nd->first, it_2nd->second);
    std::cout << comp(pair_1st, pair_2nd) << std::endl;
  }

  void test_op_compare() {
    pout("op_compare");
    map_t map(original_);
    const map_t c_map(original_);
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
  template < typename Map >
  void print_info(Map map) {
    for (citer_t it = map.begin(); it != map.end(); it++) {
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

  deque_t src_deq1_;
  deque_t src_deq2_;
  size_t default_size_;
  map_t original_;
  pair_t new_pair_;
};

#endif
