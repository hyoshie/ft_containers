#ifndef PAIRTESTER_HPP
#define PAIRTESTER_HPP

#if USE_STL
#define NAMESPACE std
#include <utility>
#else
#define NAMESPACE ft
#include "pair.hpp"
#endif

#include <iostream>

#include "output_util.hpp"

template < typename T1, typename T2, typename Cont1, typename Cont2 >
class PairTester {
 public:
  PairTester(const Cont1 &c1, const Cont2 &c2) : c1_(c1), c2_(c2) {}

  void run() {
    test_ctor();
    test_op_equal();
    // 非メンバ関数
    test_make_pair();
    test_op_compare();
  }

  void test_ctor() {
    pout("ctor");
    ft::pair< T1, T2 > default_p;
    ft::pair< T1, T2 > p(c1_.back(), c2_.back());
    ft::pair< T1, T2 > copy(p);
    ft::pair< char, std::string > copy2(p);
    print_info(default_p);
    print_info(p);
    print_info(copy);
    print_info(copy2);
  }

  void test_op_equal() {
    pout("op_equal");
    ft::pair< T1, T2 > p(c1_.back(), c2_.back());
    ft::pair< T1, T2 > p2(c1_.front(), c2_.front());
    p = p2;
    print_info(p);
  }

  void test_make_pair() {
    pout("test_make_pair");
    ft::pair< T1, T2 > p = ft::make_pair(c1_.back(), c2_.back());
    print_info(p);
  }

  void test_op_compare() {
    pout("op_compare");
    ft::pair< T1, T2 > large_p(c1_.back(), c2_.back());
    ft::pair< T1, T2 > small_p(c1_.front(), c2_.front());
    ft::pair< T1, T2 > small_p2(c1_.front(), c2_.back());
    ft::pair< T1, T2 > copy(large_p);

    std::cout << (large_p == copy) << std::endl;
    std::cout << (large_p != copy) << std::endl;
    std::cout << (small_p < large_p) << std::endl;
    std::cout << (small_p < small_p2) << std::endl;
    std::cout << (small_p <= large_p) << std::endl;
    std::cout << (large_p <= copy) << std::endl;
    std::cout << (large_p > small_p) << std::endl;
    std::cout << (large_p >= copy) << std::endl;
  }

 private:
  template < typename Pair >
  void print_info(Pair &p) {
    std::cout << "{ " << p.first << ", " << p.second << "}" << std::endl;
  }

  Cont1 c1_;
  Cont2 c2_;
};

#endif /* PAIRTESTER_HPP */
