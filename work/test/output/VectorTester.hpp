#ifndef VECTORTESTER_HPP
#define VECTORTESTER_HPP

#if USE_STL
#define NAMESPACE std
#include <vector>
#else
#define NAMESPACE ft
#include "vector.hpp"
#endif

#include <deque>
#include <iostream>

#include "IteratorTester.hpp"

template < typename T >
class VectorTester {
 private:
  typedef T value_t;
  typedef NAMESPACE::vector< T > vector_t;
  typedef typename vector_t::iterator iter_t;
  typedef typename std::deque< T > deque_t;

 public:
  static const int kElemCount = 1000;

  VectorTester(const deque_t& deque)
      : src_deq_(deque),
        original_(src_deq_.begin(), src_deq_.end()),
        value_(src_deq_[src_deq_.size() / 2]) {}

  void run() {
    std::cout << std::boolalpha;

    test_ctor();
    test_iter();
    test_op_equal();
    test_assign();
    test_get_allocator();
    // 要素アクセス
    test_at();
    test_op_subscript();
    test_front();
    test_back();
    // イテレーター
    test_begin();
    test_end();
    test_rbegin();
    test_rend();
    // 容量
    test_empty();
    test_size();
    test_max_size();
    test_reserve();
    test_capacity();
    // 変更
    test_clear();
    test_insert();
    test_erase();
    test_push_back();
    test_pop_back();
    test_resize();
    test_swap();
    // 非メンバ関数
    test_op_compare();
  }

  void test_ctor() {
    pout("ctor");

    std::allocator< int > allocator;
    vector_t def_vec;
    vector_t alloc_vec(allocator);
    vector_t fill_vec(kElemCount, value_);
    vector_t iter_vec(src_deq_.begin(), src_deq_.end());
    vector_t copy_vec(fill_vec);

    print_info(def_vec);
    print_info(alloc_vec);
    print_info(fill_vec);
    print_info(iter_vec);
    print_info(copy_vec);
  }

  void test_iter() {
    pout("iter");

    IteratorTester< vector_t > tester(original_);
    tester.run();
  }

  void test_op_equal() {
    pout("op_equal");

    vector_t copy;

    copy = original_;
    print_info(copy);
  }

  void test_assign_fill() {
    pout("assign_fill");

    vector_t vec(1, src_deq_[0]);
    // count > capacity()
    vec.assign(5, src_deq_[1]);
    print_info(vec);
    // count > size()
    vec.reserve(10);
    vec.assign(7, src_deq_[2]);
    print_info(vec);
    // count < size()
    vec.assign(4, src_deq_[3]);
    print_info(vec);
  }

  void test_assign_range() {
    pout("assign_range");

    vector_t vec(42, value_);

    vec.assign(src_deq_.begin(), src_deq_.end());
    print_info(vec);
  }

  void test_assign() {
    test_assign_fill();
    test_assign_range();
  }

  void test_get_allocator() {
    pout("get_allocator");

    std::allocator< value_t > allocator;

    std::cout << (original_.get_allocator() == allocator) << std::endl;
  }

  void test_at() {
    pout("at");

    std::cout << original_.at(0) << std::endl;

    try {
      std::cout << original_.at(original_.size()) << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "catch std::out_of_range" << std::endl;
    }
  }

  void test_op_subscript() {
    pout("op_subscript");

    vector_t vec(original_);

    std::cout << vec[1] << std::endl;
    vec[1] = value_;
    std::cout << vec[1] << std::endl;

    std::cout << original_[1] << std::endl;
  }

  void test_front() {
    pout("front");

    vector_t vec(original_);

    std::cout << vec.front() << std::endl;
    vec.front() = value_;
    std::cout << vec.front() << std::endl;

    std::cout << original_.front() << std::endl;
  }

  void test_back() {
    pout("back");

    vector_t vec(original_);

    std::cout << vec.back() << std::endl;
    vec.back() = value_;
    std::cout << vec.back() << std::endl;

    std::cout << original_.back() << std::endl;
  }

  void test_begin() {
    pout("begin");

    std::cout << *(original_.begin()) << std::endl;
  }

  void test_end() {
    pout("end");

    std::cout << *--(original_.end()) << std::endl;
  }

  void test_rbegin() {
    pout("rbegin");

    std::cout << *(original_.rbegin()) << std::endl;
  }

  void test_rend() {
    pout("rend");

    std::cout << *--(original_.rbegin()) << std::endl;
  }

  void test_empty() {
    pout("empty");

    const vector_t def_vec;

    std::cout << def_vec.empty() << std::endl;
    std::cout << original_.empty() << std::endl;
  }

  void test_size() {
    pout("size");

    const vector_t def_vec;

    std::cout << def_vec.empty() << std::endl;
    std::cout << original_.size() << std::endl;
  }

  void test_max_size() {
    pout("max_size");

    std::cout << original_.max_size() << std::endl;
  }

  void test_reserve() {
    pout("reserve");

    vector_t vec(5, value_);

    vec.reserve(1);
    print_info(vec);
    vec.reserve(5);
    print_info(vec);
    vec.reserve(100);
    print_info(vec);
    try {
      vec.reserve(vec.max_size() + 1);
    } catch (const std::length_error& e) {
      std::cout << "catch std::out_of_range" << std::endl;
    }
  }

  void test_capacity() {
    pout("capacity");

    vector_t def_vec;

    std::cout << def_vec.capacity() << std::endl;
    std::cout << original_.capacity() << std::endl;
  }

  void test_clear() {
    pout("clear");

    vector_t def_vec;
    vector_t vec(original_);

    def_vec.clear();
    vec.clear();
    print_info(def_vec);
    print_info(vec);
  }

  void test_insert_one() {
    pout("insert_one");

    vector_t vec(original_);
    iter_t it = vec.begin();

    it = vec.insert(it, value_);
    std::cout << *it << std::endl;
    print_info(vec);

    it = vec.begin() + 4;
    it = vec.insert(it, value_);
    std::cout << *it << std::endl;
    print_info(vec);
  }

  void test_insert_fill() {
    pout("insert_fll");

    vector_t vec(original_);
    iter_t it = vec.begin() + 4;

    vec.insert(it, 100, value_);
    print_info(vec);
  }

  void test_insert_range() {
    pout("insert_range");

    vector_t vec(original_);
    iter_t it = vec.begin() + 4;

    vec.insert(it, src_deq_.begin(), src_deq_.end());
    print_info(vec);
  }

  void test_insert() {
    test_insert_one();
    test_insert_fill();
    test_insert_range();
  }

  void test_erase_one() {
    pout("erase_one");
    vector_t vec(original_);

    iter_t it = vec.begin() + 1;
    it = vec.erase(it);
    std::cout << *it << std::endl;
    print_info(vec);

    // pos が最後の要素を参照する場合は、 end() イテレータが返されます。
    it = --vec.end();
    std::cout << *it << std::endl;
    it = vec.erase(it);
    print_info(vec);
    std::cout << (it == vec.end()) << std::endl;
  }

  void test_erase_range() {
    pout("erase_range");
    vector_t vec(original_);

    iter_t it = vec.begin() + 1;
    iter_t ite = vec.begin() + 3;

    it = vec.erase(it, ite);
    print_info(vec);
    std::cout << *it << std::endl;

    // 削除前に last==end() であった場合は、更新後の end()
    // イテレータが返されます
    ite = vec.end();
    it = vec.erase(it, ite);
    print_info(vec);
    std::cout << (*it != *ite) << std::endl << (*it == *vec.end()) << std::endl;

    // [first, last) が空範囲の場合は、 last が返されます。
    it = vec.begin();
    it = vec.erase(it, it);
    print_info(vec);
    std::cout << (it == vec.begin()) << std::endl;
  }

  void test_erase() {
    test_erase_one();
    test_erase_range();
  }

  void test_push_back() {
    pout("push_back");

    vector_t def_vec;
    vector_t vec(original_);

    def_vec.push_back(value_);
    vec.push_back(value_);
    print_info(def_vec);
    print_info(vec);
  }

  void test_pop_back() {
    pout("pop_back");

    vector_t vec(original_);

    vec.pop_back();
    print_info(vec);
  }

  void test_resize() {
    pout("resize");

    vector_t vec(5, value_);
    vec.resize(5);
    print_info(vec);
    vec.resize(4);
    print_info(vec);
    //   guacamoleだとokなので一旦コメントアウト
    // vec.resize(6);
    // print_info(vec);
  }

  void test_swap() {
    pout("swap");

    vector_t first(5, value_);
    vector_t second(original_);
    iter_t first_it = first.begin();
    iter_t second_it = second.begin();

    first.swap(second);
    print_info(first);
    print_info(second);
    std::cout << *first_it << std::endl;
    std::cout << *second_it << std::endl;

    std::swap(first, second);
    print_info(first);
    print_info(second);
    std::cout << *first_it << std::endl;
    std::cout << *second_it << std::endl;
  }

  void test_op_compare() {
    pout("op_compare");

    vector_t vec(original_);
    vector_t copy(vec);
    vector_t large(vec);
    large.push_back(value_);

    // 同じ
    std::cout << (vec == copy) << std::endl;
    std::cout << (vec != copy) << std::endl;
    std::cout << (vec < copy) << std::endl;
    std::cout << (vec <= copy) << std::endl;
    std::cout << (vec > copy) << std::endl;
    std::cout << (vec >= copy) << std::endl;

    // 違う
    std::cout << (vec == large) << std::endl;
    std::cout << (vec != large) << std::endl;
    std::cout << (vec < large) << std::endl;
    std::cout << (vec <= large) << std::endl;
    std::cout << (vec > large) << std::endl;
    std::cout << (vec >= large) << std::endl;

    // constとの比較
    std::cout << (vec == original_) << std::endl;
    std::cout << (vec != original_) << std::endl;
    std::cout << (vec < original_) << std::endl;
    std::cout << (vec <= original_) << std::endl;
    std::cout << (vec > original_) << std::endl;
    std::cout << (vec >= original_) << std::endl;
  }

 private:
  // template < typename U >
  // void pout(U vec) {
  //   static int no;
  //   std::cout << std::endl;
  //   std::cout << "--- [" << ++no << "]:" << vec << " ---" << std::endl;
  // }

  template < typename Vec >
  void print_info(Vec& vec) {
    std::cout << "size:" << vec.size() << " capacity:" << vec.capacity()
              << std::endl;
    std::cout << "{ ";
    for (typename Vec::iterator it = vec.begin(); it != vec.end(); ++it)
      std::cout << *it << " ";
    std::cout << "}" << std::endl;
  }
  deque_t src_deq_;
  const vector_t original_;
  value_t value_;
};

#endif /* VECTORTESTER_HPP */
