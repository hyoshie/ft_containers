#ifndef SETTESTER_HPP
#define SETTESTER_HPP

#if USE_STL
#define NAMESPACE std
#include <set>
#else
#define NAMESPACE ft
#include "set.hpp"
#endif

#include <deque>
#include <functional>
#include <iostream>

#include "IteratorTester.hpp"

template < typename Key, typename Compare = std::less< Key > >
class SetTester {
 private:
  // 型
  typedef Key key_t;
  typedef NAMESPACE::set< Key, Compare > set_t;
  typedef typename set_t::iterator iter_t;
  typedef typename set_t::const_iterator citer_t;
  typedef typename std::deque< key_t > deque_t;

 public:
  static const int kElemCount = 1000;

  // メンバ関数
  SetTester(deque_t deq1, deque_t deq2, key_t min)
      : src_deq1_(deq1),
        src_deq2_(deq2),
        default_size_(deq1.size()),
        original_(src_deq1_.begin(), src_deq1_.end()),
        min_(min) {}

  void run() {
    std::cout << std::boolalpha;
    test_ctor();
    test_iter();
    test_op_assign();
    // print_graphを仕込んでいるので一旦コメントアウト
    // test_get_allocator();
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
    // // 木を表示
    // print_graph();
  }

  void test_default_ctor() {
    pout("default ctor");
    set_t def_set;
    print_basic_info(def_set);
  }

  void test_arg_ctor() {
    pout("arg ctor");
    std::greater< Key > comp;
    std::allocator< key_t > alloc;
    NAMESPACE::set< Key, std::greater< Key > > arg_set(comp, alloc);
    arg_set.insert(min_);
    print_basic_info(arg_set);
  }

  void test_range_ctor() {
    pout("range ctor");
    std::greater< Key > comp;
    std::allocator< key_t > alloc;
    NAMESPACE::set< Key, std::greater< Key > > range_set(
        src_deq2_.begin(), src_deq2_.end(), comp, alloc);
    print_basic_info(range_set);
  }

  void test_copy_ctor() {
    pout("copy ctor");
    set_t copy(original_);
    print_basic_info(copy);
  }

  void test_iter() {
    pout("iter");

    IteratorTester< set_t > tester(original_);
    tester.run();
  }

  void test_get_allocator() {
    pout("get_allocator");
    std::allocator< key_t > alloc;
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
    set_t set;
    set.insert(min_);
    set = original_;
    print_basic_info(set);
  }

  void test_begin_and_end() {
    pout("begin and end");

    print_value(*(original_.begin()));
    print_value(*--(original_.end()));
  }

  void test_rbegin_and_rend() {
    pout("begin and end");

    print_value(*(original_.rbegin()));
    print_value(*(original_.rbegin()));
  }

  void test_empty() {
    pout("empty");
    const set_t def_set;

    std::cout << def_set.empty() << std::endl;
    std::cout << original_.empty() << std::endl;
  }

  void test_size() {
    pout("size");
    const set_t def_set;

    std::cout << def_set.size() << std::endl;
    std::cout << original_.size() << std::endl;
  }

  void test_max_size() {
    pout("size");
    const set_t c_set(original_);

    std::cout << original_.max_size() << std::endl;
  }

  void test_clear() {
    pout("clear");
    set_t set(original_);

    set.clear();
    print_basic_info(set);
  }

  void test_insert1() {
    pout("insert1");
    set_t set(original_);
    iter_t it = set.begin();

    // 成功
    NAMESPACE::pair< iter_t, bool > result = set.insert(min_);
    print_value(*(result.first));
    std::cout << result.second << std::endl;
    // 失敗
    result = set.insert(min_);
    print_value(*(result.first));
    std::cout << result.second << std::endl;

    print_basic_info(set);

    // insert前のiteratorが有効かの確認
    print_iter(it);
  }

  void test_insert_hint() {
    pout("insert_hint");
    set_t set(original_);
    iter_t it = set.begin();
    iter_t hint = set.begin();

    // 成功
    iter_t result = set.insert(hint, min_);
    print_value(*result);
    // 失敗
    result = set.insert(hint, min_);
    print_value(*result);

    print_basic_info(set);
    // insert前のiteratorが有効かの確認
    print_iter(it);
  }

  void test_insert_range() {
    pout("insert_range");
    set_t set(original_);
    iter_t it = set.begin();

    set.insert(src_deq2_.begin(), src_deq2_.end());
    print_basic_info(set);
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
    set_t set(original_);
    iter_t it = set.begin();
    iter_t it_2nd = ++set.begin();

    set.erase(it_2nd);
    print_basic_info(set);
    // erase前のiteratorが有効かの確認
    print_iter(it);
  }

  void test_erase_from_key() {
    pout("erase_key");
    set_t set(original_);
    iter_t it = set.begin();
    iter_t it_2nd = ++set.begin();

    set.erase(it_2nd);
    print_basic_info(set);
    // erase前のiteratorが有効かの確認
    print_iter(it);
  }

  void test_erase_range() {
    pout("erase_range");
    set_t set(original_);
    iter_t it = set.begin();
    iter_t it_2nd = ++set.begin();
    iter_t it_last = --set.end();

    set.erase(it_2nd, it_last);
    print_basic_info(set);
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
    set_t set(original_);
    set_t added(original_);
    added.insert(min_);

    //メソッド
    set.swap(added);
    print_basic_info(set);
    print_basic_info(added);

    //非メソッド
    std::swap(set, added);
    print_basic_info(set);
    print_basic_info(added);
  }

  void test_count() {
    pout("count");

    citer_t found = original_.begin();
    // 1
    std::cout << original_.count(*found) << std::endl;
    // 0
    std::cout << original_.count(min_) << std::endl;
  }

  void test_find() {
    pout("find");

    // 成功
    key_t key = *original_.begin();
    citer_t c_found = original_.find(key);

    print_iter(c_found);

    // 失敗
    key = min_;
    citer_t c_not_found = original_.find(key);

    std::cout << (c_not_found == original_.end()) << std::endl;
  }

  void test_equal_range() {
    pout("equal_range");

    // 存在するkey
    key_t key = *original_.begin();
    NAMESPACE::pair< citer_t, citer_t > c_pair = original_.equal_range(key);

    print_iter_range(c_pair.first, c_pair.second);

    // 存在しないkey
    key = min_;
    std::cout << key << std::endl;
    c_pair = original_.equal_range(key);

    print_iter_range(c_pair.first, c_pair.second);
  }

  void test_lower_bound() {
    pout("lower_bound");

    // 存在するkey
    key_t key = *original_.begin();
    citer_t c_found = original_.lower_bound(key);

    print_iter(c_found);

    // 存在しないkey、minより下
    key = min_;
    c_found = original_.lower_bound(key);

    print_iter(c_found);

    // 存在しないkey、maxより上
    citer_t last = --original_.end();

    key = *last;
    key++;
    citer_t c_not_found = original_.lower_bound(key);

    std::cout << (c_not_found == original_.end()) << std::endl;
  }

  void test_upper_bound() {
    pout("upper_bound");

    // 存在するkey
    key_t key = *original_.begin();
    citer_t c_found = original_.upper_bound(key);

    print_iter(c_found);

    // 存在しないkey、minより下
    key = min_;
    c_found = original_.upper_bound(key);

    print_iter(c_found);

    // 存在しないkey、maxより上
    citer_t last = --original_.end();

    key = *last;
    key++;
    citer_t c_not_found = original_.upper_bound(key);

    std::cout << (c_not_found == original_.end()) << std::endl;
  }

  void print_graph() {
    pout("get_allocator");
    std::allocator< key_t > alloc;
    std::cout << std::boolalpha << (alloc == original_.get_allocator())
              << std::endl;
  }

  void test_key_comp() {
    pout("key_comp");

    Compare comp = original_.key_comp();
    citer_t it_1st = original_.begin();
    citer_t it_2nd = ++original_.begin();
    std::cout << comp(*it_1st, *it_2nd) << std::endl;
  }

  void test_value_comp() {
    pout("value_comp");

    Compare comp = original_.value_comp();
    citer_t it_1st = original_.begin();
    citer_t it_2nd = ++original_.begin();
    std::cout << comp(*it_1st, *it_2nd) << std::endl;
  }

  void test_op_compare() {
    pout("op_compare");
    set_t set(original_);
    set_t added(original_);
    added.insert(min_);

    // 同じ。ついでにconstもチェック
    std::cout << (original_ == set) << std::endl;
    std::cout << (original_ != set) << std::endl;
    std::cout << (original_ < set) << std::endl;
    std::cout << (original_ <= set) << std::endl;
    std::cout << (original_ > set) << std::endl;
    std::cout << (original_ >= set) << std::endl;

    // 違う
    std::cout << (added == set) << std::endl;
    std::cout << (added != set) << std::endl;
    std::cout << (added < set) << std::endl;
    std::cout << (added <= set) << std::endl;
    std::cout << (added > set) << std::endl;
    std::cout << (added >= set) << std::endl;
  }

 private:
  deque_t src_deq1_;
  deque_t src_deq2_;
  size_t default_size_;
  const set_t original_;
  key_t min_;
};

#endif /* SETTESTER_HPP */
