#include <deque>

#include "Fixed.hpp"
#include "VectorTester.hpp"

static void test_int() {
  std::deque< int > int_deq;
  int elem_count = VectorTester< int >::kElemCount;
  for (int i = 0; i < elem_count; i++) {
    int_deq.push_back(i);
  }

  VectorTester< int > vec_tester(int_deq);
  vec_tester.run();
}

static void test_primitive() {
  test_int();
  // test_base_stdlist();
  // test_base_stddeq();
}

void test_vector() {
  test_primitive();
  // test_user_defined();
}

// typedef ft::vector< int >::iterator ft_intvec_iter;
// typedef ft::vector< int >::reverse_iterator ft_intvec_riter;

// #define std::cout std::std::cout
// #define std::endl std::std::endl

// template < typename T >
// void pout(T s) {
//   static int no;
//   std::cout << std::endl;
//   std::cout << "--- [" << ++no << "]:" << s << " ---" << std::endl;
// }

// template < class T >
// void vdebug(T& V) {
//   std::cout << "size:" << V.size() << " capacity:" << V.capacity() <<
//   std::endl; std::cout << "{ "; for (typename T::iterator it = V.begin(); it
//   != V.end(); ++it)
//     std::cout << *it << " ";
//   std::cout << "}" << std::endl;
// }

// ft::vector< int > base_v;

// void test_type() {
//   pout("type");

//   ft::vector< int > default_v;
//   std::cout << std::boolalpha;
//   std::cout << (typeid(ft::vector< int >::value_type) == typeid(int)) <<
//   std::endl; std::cout << (typeid(ft::vector< int >::allocator_type) ==
//            typeid(std::allocator< int >))
//        << std::endl;
//   std::cout << (typeid(ft::vector< int >::size_type) == typeid(std::size_t))
//   << std::endl; std::cout << (typeid(ft::vector< int >::difference_type) ==
//   typeid(std::ptrdiff_t))
//        << std::endl;
//   std::cout << (typeid(ft::vector< int >::pointer) == typeid(int*)) <<
//   std::endl; std::cout << (typeid(ft::vector< int >::const_pointer) ==
//   typeid(const int*))
//        << std::endl;
//   std::cout << (typeid(ft::vector< int >::reference) == typeid(int&)) <<
//   std::endl; std::cout << (typeid(ft::vector< int >::const_reference) ==
//   typeid(const int&))
//        << std::endl;
// }

// // void test_iterator() {
// //   pout("iterator");

// //   ft::vector< int > v;
// //   for (int i = 0; i < 20; i++) {
// //     v.push_back(i);
// //   }
// //   ft::vector< int >::iterator it = v.begin();
// //   ft::vector< int >::iterator first = v.begin();

// //   // input_it
// //   std::cout << *it << std::endl;
// //   std::cout << *++it << std::endl;
// //   std::cout << *it << std::endl;
// //   std::cout << *it++ << std::endl;
// //   std::cout << *it << std::endl;
// //   std::cout << (it == first) << std::endl;
// //   std::cout << (it != first) << std::endl;
// //   // output_it
// //   *it = 42;
// //   std::cout << *it << std::endl;
// //   // forward_it
// //   ft::vector< int >::iterator copy = it;
// //   ++it;
// //   ++copy;
// //   std::cout << (it == copy) << std::endl;
// //   // bidirectional_it
// //   std::cout << *--it << std::endl;
// //   std::cout << *it << std::endl;
// //   std::cout << *it-- << std::endl;
// //   std::cout << *it << std::endl;
// //   // random_it
// //   it += 3;
// //   std::cout << *it << std::endl;
// //   it -= 3;
// //   std::cout << *it << std::endl;
// //   it = it + 3;
// //   std::cout << *it << std::endl;
// //   it = it - 3;
// //   std::cout << *it << std::endl;
// //   it = 3 + it;
// //   std::cout << *it << std::endl;
// //   std::cout << it - first << std::endl;
// //   std::cout << it[3] << std::endl;
// //   std::cout << (it < first) << std::endl;
// //   std::cout << (it <= first) << std::endl;
// //   std::cout << (it > first) << std::endl;
// //   std::cout << (it >= first) << std::endl;
// // }

// void test_at() {
//   pout("at");
//   ft::vector< int > v;
//   for (int i = 0; i < 5; i++) {
//     v.push_back(i);
//   }
//   std::cout << v.at(0) << std::endl;
//   try {
//     std::cout << v.at(5) << std::endl;
//   } catch (const std::out_of_range& e) {
//     std::cout << "catch std::out_of_range" << std::endl;
//   }
//   // const
//   const ft::vector< int > cv(v);
//   std::cout << cv.at(4) << std::endl;
//   try {
//     std::cout << cv.at(5) << std::endl;
//   } catch (const std::out_of_range& e) {
//     std::cout << "catch std::out_of_range" << std::endl;
//   }
// }

// void test_op_subscript() {
//   pout("op_subscript");
//   ft::vector< int > v;
//   for (int i = 0; i < 5; i++) {
//     v.push_back(i);
//   }
//   std::cout << v[0] << std::endl;
//   // const
//   const ft::vector< int > cv(v);
//   std::cout << cv[4] << std::endl;
// }

// void test_front() {
//   pout("front");
//   ft::vector< int > v;
//   for (int i = 0; i < 5; i++) {
//     v.push_back(i);
//   }
//   std::cout << v.front() << std::endl;
//   // const
//   const ft::vector< int > cv(v);
//   std::cout << cv.front() << std::endl;
// }

// void test_back() {
//   pout("back");
//   ft::vector< int > v;
//   for (int i = 0; i < 5; i++) {
//     v.push_back(i);
//   }
//   std::cout << v.back() << std::endl;
//   // const
//   const ft::vector< int > cv(v);
//   std::cout << cv.back() << std::endl;
// }

// void test_begin() {
//   pout("begin");
//   ft::vector< int > v;
//   for (int i = 0; i < 5; i++) {
//     v.push_back(i);
//   }
//   std::cout << *(v.begin()) << std::endl;
//   // const
//   const ft::vector< int > cv(v);
//   std::cout << *(cv.begin()) << std::endl;
// }

// void test_end() {
//   pout("end");
//   ft::vector< int > v;
//   for (int i = 0; i < 5; i++) {
//     v.push_back(i);
//   }
//   std::cout << *--(v.end()) << std::endl;
//   // const
//   const ft::vector< int > cv(v);
//   std::cout << *--(cv.end()) << std::endl;
// }

// void test_rbegin() {
//   pout("rbegin");
//   ft::vector< int > v;
//   for (int i = 0; i < 5; i++) {
//     v.push_back(i);
//   }
//   std::cout << *(v.rbegin()) << std::endl;
//   // const
//   const ft::vector< int > cv(v);
//   std::cout << *(cv.rbegin()) << std::endl;
// }

// void test_rend() {
//   pout("rend");
//   ft::vector< int > v;
//   for (int i = 0; i < 5; i++) {
//     v.push_back(i);
//   }
//   std::cout << *--(v.rend()) << std::endl;
//   // const
//   const ft::vector< int > cv(v);
//   std::cout << *--(cv.rend()) << std::endl;
// }

// void test_empty() {
//   pout("empty");
//   ft::vector< int > nocontent_v;
//   ft::vector< int > content_v;
//   for (int i = 0; i < 5; i++) {
//     content_v.push_back(i);
//   }
//   std::cout << std::boolalpha;
//   std::cout << nocontent_v.empty() << std::endl;
//   std::cout << content_v.empty() << std::endl;
//   // const
//   const ft::vector< int > nocontent_cv(nocontent_v);
//   const ft::vector< int > content_cv(content_v);
//   std::cout << nocontent_cv.empty() << std::endl;
//   std::cout << content_cv.empty() << std::endl;
// }

// void test_size() {
//   pout("size");
//   ft::vector< int > nocontent_v;
//   ft::vector< int > content_v;
//   for (int i = 0; i < 5; i++) {
//     content_v.push_back(i);
//   }
//   std::cout << std::boolalpha;
//   std::cout << nocontent_v.size() << std::endl;
//   std::cout << content_v.size() << std::endl;
//   // const
//   const ft::vector< int > nocontent_cv(nocontent_v);
//   const ft::vector< int > content_cv(content_v);
//   std::cout << nocontent_cv.size() << std::endl;
//   std::cout << content_cv.size() << std::endl;
// }

// void test_max_size() {
//   pout("max_size");

//   ft::vector< int > v(5, 42);
//   std::cout << v.max_size() << std::endl;
// }

// void test_reserve() {
//   pout("reserve");

//   ft::vector< int > v(5, 42);
//   v.reserve(1);
//   vdebug(v);
//   v.reserve(5);
//   vdebug(v);
//   v.reserve(100);
//   vdebug(v);
//   try {
//     v.reserve(v.max_size() + 1);
//   } catch (const std::length_error& e) {
//     std::cout << "catch std::out_of_range" << std::endl;
//   }
// }

// void test_capacity() {
//   pout("capacity");

//   ft::vector< int > default_v;
//   ft::vector< int > v(5, 42);
//   std::cout << default_v.capacity() << std::endl;
//   std::cout << v.capacity() << std::endl;
//   // const
//   const ft::vector< int > default_cv(default_v);
//   const ft::vector< int > cv(v);
//   std::cout << default_cv.size() << std::endl;
//   std::cout << cv.size() << std::endl;
// }

// void test_clear() {
//   pout("clear");

//   ft::vector< int > default_v;
//   ft::vector< int > v(5, 42);
//   default_v.clear();
//   v.clear();
//   vdebug(default_v);
//   vdebug(v);
// }

// void test_insert_one() {
//   pout("insert_one");

//   ft::vector< int > v(base_v);
//   ft_intvec_iter it = v.begin();
//   it = v.insert(it, 100);
//   std::cout << *it << std::endl;
//   vdebug(v);
//   it = v.begin() + 4;
//   it = v.insert(it, 200);
//   vdebug(v);
//   std::cout << *it << std::endl;
// }

// void test_insert_multi() {
//   pout("insert_multi");

//   // void insert(iterator pos, size_type count, const T& value) {
//   ft::vector< int > v(base_v);
//   ft_intvec_iter it = v.begin() + 4;
//   v.insert(it, 500, 300);
//   vdebug(v);
//   it = v.begin() + 4;
//   v.insert(it, 0, 400);
//   vdebug(v);
// }

// void test_insert_range() {
//   pout("insert_range");

//   // void insert(iterator pos, InputIterator first, InputIterator last,
//   //             typename ft::enable_if< !ft::is_integral< InputIterator
//   //             >::value,
//   //                                     InputIterator >::type* = NULL);

//   ft::vector< int > v(base_v);
//   std::list< int > list;
//   for (int i = 0; i < 5; i++) {
//     list.push_back(i * 10);
//   }
//   std::list< int >::iterator l_it = list.begin();
//   std::list< int >::iterator l_ite = list.end();
//   l_it++;
//   l_ite--;
//   ft_intvec_iter it = v.begin() + 4;
//   v.insert(it, l_it, l_ite);
//   vdebug(v);
// }

// void test_insert() {
//   test_insert_one();
//   //   guacamoleだとokなので一旦コメントアウト
//   // test_insert_multi();
//   test_insert_range();
// }

// void test_erase_one() {
//   pout("erase_one");
//   ft::vector< int > v(base_v);

//   ft_intvec_iter it = v.begin() + 1;
//   it = v.erase(it);
//   vdebug(v);
//   std::cout << *it << std::endl;
//   // stlでcrash
//   // it = v.end();
//   // it = v.erase(it);
//   // vdebug(v);
//   // std::cout << *it << std::endl;

//   // pos が最後の要素を参照する場合は、 end() イテレータが返されます。
//   it = --v.end();
//   std::cout << *it << std::endl;
//   it = v.erase(it);
//   vdebug(v);
//   std::cout << (it == v.end()) << std::endl;
// }

// void test_erase_range() {
//   pout("erase_range");
//   ft::vector< int > v(base_v);

//   ft_intvec_iter it = v.begin() + 1;
//   ft_intvec_iter ite = v.begin() + 3;
//   it = v.erase(it, ite);
//   vdebug(v);
//   std::cout << *it << std::endl;
//   // 削除前に last==end() であった場合は、更新後の end()
//   イテレータが返されます ite = v.end(); it = v.erase(it, ite); vdebug(v);
//   std::cout << (*it != *ite) << std::endl << (*it == *v.end()) << std::endl;
//   // [first, last) が空範囲の場合は、 last が返されます。
//   it = v.begin();
//   it = v.erase(it, it);
//   vdebug(v);
//   std::cout << (it == v.begin()) << std::endl;
// }

// void test_erase() {
//   test_erase_one();
//   test_erase_range();
// }

// void test_push_back() {
//   pout("push_back");
//   ft::vector< int > default_v;
//   ft::vector< int > v(5, 42);
//   default_v.push_back(219);
//   v.push_back(219);
//   vdebug(default_v);
//   vdebug(v);
// }

// void test_pop_back() {
//   pout("pop_back");

//   // segv
//   // ft::vector< int > default_v;
//   //  default_v.pop_back();
//   // vdebug(default_v);
//   ft::vector< int > v(5, 42);
//   v.pop_back();
//   vdebug(v);
// }

// void test_resize() {
//   pout("resize");

//   ft::vector< int > v(5, 42);
//   v.resize(5);
//   vdebug(v);
//   v.resize(4);
//   vdebug(v);
//   //   guacamoleだとokなので一旦コメントアウト
//   // v.resize(6);
//   // vdebug(v);
// }

// void test_op_compare() {
//   pout("op_compare");

//   ft::vector< int > v(5, 42);
//   ft::vector< int > copy(v);
//   ft::vector< int > large_v(v);
//   large_v[2] = 43;

//   std::cout << (v == copy) << std::endl;
//   std::cout << (v != copy) << std::endl;
//   std::cout << (v < large_v) << std::endl;
//   std::cout << (v <= large_v) << std::endl;
//   std::cout << (v <= copy) << std::endl;
//   std::cout << (large_v >= v) << std::endl;
//   std::cout << (v >= copy) << std::endl;
// }

// void test_swap() {
//   pout("swap");

//   ft::vector< int > v(5, 42);
//   ft::vector< int > v2(2, 21);

//   vdebug(v);
//   vdebug(v2);
//   std::swap(v, v2);
//   vdebug(v);
//   vdebug(v2);
// }

// void create_base_vec() {
//   for (int i = 0; i < 5; i++) {
//     base_v.push_back(i);
//   }
// }

// void test_vector() {
//   create_base_vec();

//   test_type();
//   // test_iterator();

//   test_constructor();
//   test_op_equal();
//   test_assign();
//   test_get_allocator();
//   // 要素アクセス
//   test_at();
//   test_op_subscript();
//   test_front();
//   test_back();
//   // イテレーター
//   test_begin();
//   test_end();
//   test_rbegin();
//   test_rend();
//   // 容量
//   test_empty();
//   test_size();
//   test_max_size();
//   test_reserve();
//   test_capacity();
//   // 変更
//   test_clear();
//   test_insert();
//   test_erase();
//   test_push_back();
//   test_pop_back();
//   test_resize();
//   // 非メンバ関数
//   test_op_compare();
//   test_swap();
// }

// // get_allocatorに自作allocator入れる
