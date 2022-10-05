#ifndef ITERATORTESTER_HPP
#define ITERATORTESTER_HPP

#include <typeinfo>

#include "output_util.hpp"

template < typename Container >
class IteratorTester {
 private:
  typedef typename Container::iterator iter_t;
  typedef typename Container::const_iterator citer_t;
  typedef typename Container::reverse_iterator riter_t;
  typedef typename Container::const_reverse_iterator criter_t;
  typedef typename iter_t::iterator_category iter_category_t;

 public:
  IteratorTester(const Container& c)
      : c_(c),
        first_(c_.begin()),
        cfirst_(c_.begin()),
        rfirst_(c_.rbegin()),
        crfirst_(c_.rbegin()),
        tag_(iter_category_t()) {}

  void run() { run(tag_); }

 private:
  void run(std::random_access_iterator_tag tag) {
    (void)tag;
    test_random_access_iter(first_);
    test_random_access_iter(cfirst_);
    test_random_access_iter(rfirst_);
    test_random_access_iter(crfirst_);

    // constとの比較
    test_op_equality(++first_, cfirst_);
    test_op_relational(first_, cfirst_);
  }

  void run(std::bidirectional_iterator_tag tag) {
    (void)tag;
    test_bidirectional_iter(first_);
    test_bidirectional_iter(cfirst_);
    test_bidirectional_iter(rfirst_);
    test_bidirectional_iter(crfirst_);

    // constとの比較
    test_op_equality(++first_, cfirst_);
  }

  template < typename Iter >
  void test_random_access_iter(Iter it) {
    test_bidirectional_iter(it);

    pout("random_access_iter");

    Iter copy(it);
    it += 3;
    std::cout << *it << std::endl;
    it -= 3;
    std::cout << *it << std::endl;

    it = it + 3;
    std::cout << *it << std::endl;
    it = 3 + it;
    std::cout << *it << std::endl;
    it = it - 3;
    std::cout << *it << std::endl;

    std::cout << it - copy << std::endl;

    std::cout << it[3] << std::endl;

    test_op_relational(it, copy);
  }

  template < typename Iter >
  void test_bidirectional_iter(Iter it) {
    test_forward_iter(it);

    pout("bidirectional_iter");

    std::cout << *it << std::endl;
    it++;
    it++;
    std::cout << *--it << std::endl;
    std::cout << *it << std::endl;
    std::cout << *it-- << std::endl;
    std::cout << *it << std::endl;
  }

  template < typename Iter >
  void test_forward_iter(Iter it) {
    test_input_iter(it);
    test_output_iter(it);

    pout("forward_iter");

    Iter copy(it);
    ++it;
    ++copy;
    std::cout << (it == copy) << std::endl;
  }

  template < typename Iter >
  void test_input_iter(Iter it) {
    pout("input_iter");

    Iter copy(it);

    std::cout << *it << std::endl;
    std::cout << *++it << std::endl;
    std::cout << *it << std::endl;
    std::cout << *it++ << std::endl;
    std::cout << *it << std::endl;
    test_op_equality(it, copy);
  }

  template < typename Iter >
  void test_output_iter(Iter it) {
    pout("output_iter");
    Iter copy(it);

    std::cout << *++it << std::endl;
    std::cout << *it++ << std::endl;
    // 本当は入れたいが、mapのpairfirstがconstなので省略。
    // それにconst_iteratorのときもできない
    // *it = *copy;
    std::cout << *it++ << std::endl;
  }

  template < typename Iter1, typename Iter2 >
  void test_op_equality(Iter1 first, Iter2 second) {
    std::cout << (first == second) << std::endl;
    std::cout << (first != second) << std::endl;
  }

  template < typename Iter1, typename Iter2 >
  void test_op_relational(Iter1 first, Iter2 second) {
    std::cout << (first < second) << std::endl;
    std::cout << (first <= second) << std::endl;
    std::cout << (first > second) << std::endl;
    std::cout << (first >= second) << std::endl;
  }

  template < typename U >
  void pout(U message) {
    static int no;
    std::cout << std::endl;
    std::cout << "--- [" << ++no << "]:" << message << " ---" << std::endl;
  }

  Container c_;
  iter_t first_;
  citer_t cfirst_;
  riter_t rfirst_;
  criter_t crfirst_;
  iter_category_t tag_;
};

#endif /* ITERATORTESTER_HPP */
