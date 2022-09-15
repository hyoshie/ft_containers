#include <algorithm>
#include <exception>
#include <iostream>
#include <list>
#include <typeinfo>

#if USE_STL
#define ft std
#include <vector>
#else
#include "vector.hpp"
#endif

typedef ft::vector< int >::iterator ft_intvec_iter;
typedef ft::vector< int >::reverse_iterator ft_intvec_riter;

#define cout std::cout
#define endl std::endl

template < typename T >
void pout(T s) {
  static int no;
  cout << endl;
  cout << "--- [" << ++no << "]:" << s << " ---" << endl;
}

template < class T >
void vdebug(T& V) {
  cout << "size:" << V.size() << " capacity:" << V.capacity() << endl;
  cout << "{ ";
  for (typename T::iterator it = V.begin(); it != V.end(); ++it)
    cout << *it << " ";
  cout << "}" << endl;
}

ft::vector< int > base_v;

void test_type() {
  pout("type");

  ft::vector< int > default_v;
  cout << std::boolalpha;
  cout << (typeid(ft::vector< int >::value_type) == typeid(int)) << endl;
  cout << (typeid(ft::vector< int >::allocator_type) ==
           typeid(std::allocator< int >))
       << endl;
  cout << (typeid(ft::vector< int >::size_type) == typeid(std::size_t)) << endl;
  cout << (typeid(ft::vector< int >::difference_type) == typeid(std::ptrdiff_t))
       << endl;
  cout << (typeid(ft::vector< int >::pointer) == typeid(int*)) << endl;
  cout << (typeid(ft::vector< int >::const_pointer) == typeid(const int*))
       << endl;
  cout << (typeid(ft::vector< int >::reference) == typeid(int&)) << endl;
  cout << (typeid(ft::vector< int >::const_reference) == typeid(const int&))
       << endl;
}

void test_constructor() {
  pout("constructer");
  std::allocator< int > allocator;
  std::list< int > list(5, 219);

  ft::vector< int > default_v;
  ft::vector< int > alloc_v(allocator);
  ft::vector< int > value_v(5, 219);
  ft::vector< int > iter_v(list.begin(), list.end());
  ft::vector< int > copy_v(value_v);
  vdebug(default_v);
  vdebug(alloc_v);
  vdebug(value_v);
  vdebug(iter_v);
  vdebug(copy_v);
}

void test_op_equal() {
  pout("op_equal");
  ft::vector< int > small_v(1, 219);
  ft::vector< int > large_v(5, 42);
  ft::vector< int > copy;
  copy = large_v;
  vdebug(copy);
  copy = small_v;
  vdebug(copy);
}

void test_assign_value() {
  pout("assign_value");
  ft::vector< int > small_v(1, 219);
  // count > capacity()
  small_v.assign(5, 42);
  vdebug(small_v);
  // count > size()
  small_v.reserve(10);
  small_v.assign(7, 43);
  vdebug(small_v);
  // count < size()
  small_v.assign(4, 4);
  vdebug(small_v);
}

void test_assign_range() {
  pout("assign_range");
  std::list< int > list;
  for (int i = 0; i < 10; i++) {
    list.push_back(i * 10);
  }
  std::list< int >::iterator l_begin = list.begin();
  std::list< int >::iterator l_it = l_begin;
  std::list< int >::iterator l_it3 = l_begin;
  std::list< int >::iterator l_it5 = l_begin;
  std::list< int >::iterator l_it7 = l_begin;
  std::list< int >::iterator l_ite = list.end();
  std::advance(l_it3, 3);
  std::advance(l_it5, 5);
  std::advance(l_it7, 7);

  ft::vector< int > small_v(1, 219);
  // count > capacity()
  small_v.assign(l_it, l_it5);
  vdebug(small_v);
  // count > size()
  small_v.reserve(10);
  small_v.assign(l_it3, l_ite);
  vdebug(small_v);
  // count < size()
  small_v.assign(l_it5, l_it7);
  vdebug(small_v);
}

void test_assign() {
  test_assign_value();
  test_assign_range();
}

void test_get_allocator() {
  pout("get_allocator");
  std::allocator< int > allocator;

  ft::vector< int > alloc_v(allocator);
  cout << std::boolalpha;
  cout << (allocator == alloc_v.get_allocator()) << endl;
  // const
  const ft::vector< int > cv(alloc_v);
  cout << (allocator == cv.get_allocator()) << endl;
}

void test_at() {
  pout("at");
  ft::vector< int > v;
  for (int i = 0; i < 5; i++) {
    v.push_back(i);
  }
  cout << v.at(0) << endl;
  try {
    cout << v.at(5) << endl;
  } catch (const std::out_of_range& e) {
    cout << "catch std::out_of_range" << endl;
  }
  // const
  const ft::vector< int > cv(v);
  cout << cv.at(4) << endl;
  try {
    cout << cv.at(5) << endl;
  } catch (const std::out_of_range& e) {
    cout << "catch std::out_of_range" << endl;
  }
}

void test_op_subscript() {
  pout("op_subscript");
  ft::vector< int > v;
  for (int i = 0; i < 5; i++) {
    v.push_back(i);
  }
  cout << v[0] << endl;
  // const
  const ft::vector< int > cv(v);
  cout << cv[4] << endl;
}

void test_front() {
  pout("front");
  ft::vector< int > v;
  for (int i = 0; i < 5; i++) {
    v.push_back(i);
  }
  cout << v.front() << endl;
  // const
  const ft::vector< int > cv(v);
  cout << cv.front() << endl;
}

void test_back() {
  pout("back");
  ft::vector< int > v;
  for (int i = 0; i < 5; i++) {
    v.push_back(i);
  }
  cout << v.back() << endl;
  // const
  const ft::vector< int > cv(v);
  cout << cv.back() << endl;
}

void test_begin() {
  pout("begin");
  ft::vector< int > v;
  for (int i = 0; i < 5; i++) {
    v.push_back(i);
  }
  cout << *(v.begin()) << endl;
  // const
  const ft::vector< int > cv(v);
  cout << *(cv.begin()) << endl;
}

void test_end() {
  pout("end");
  ft::vector< int > v;
  for (int i = 0; i < 5; i++) {
    v.push_back(i);
  }
  cout << *--(v.end()) << endl;
  // const
  const ft::vector< int > cv(v);
  cout << *--(cv.end()) << endl;
}

void test_rbegin() {
  pout("rbegin");
  ft::vector< int > v;
  for (int i = 0; i < 5; i++) {
    v.push_back(i);
  }
  cout << *(v.rbegin()) << endl;
  // const
  const ft::vector< int > cv(v);
  cout << *(cv.rbegin()) << endl;
}

void test_rend() {
  pout("rend");
  ft::vector< int > v;
  for (int i = 0; i < 5; i++) {
    v.push_back(i);
  }
  cout << *--(v.rend()) << endl;
  // const
  const ft::vector< int > cv(v);
  cout << *--(cv.rend()) << endl;
}

void test_empty() {
  pout("empty");
  ft::vector< int > nocontent_v;
  ft::vector< int > content_v;
  for (int i = 0; i < 5; i++) {
    content_v.push_back(i);
  }
  cout << std::boolalpha;
  cout << nocontent_v.empty() << endl;
  cout << content_v.empty() << endl;
  // const
  const ft::vector< int > nocontent_cv(nocontent_v);
  const ft::vector< int > content_cv(content_v);
  cout << nocontent_cv.empty() << endl;
  cout << content_cv.empty() << endl;
}

void test_size() {
  pout("size");
  ft::vector< int > nocontent_v;
  ft::vector< int > content_v;
  for (int i = 0; i < 5; i++) {
    content_v.push_back(i);
  }
  cout << std::boolalpha;
  cout << nocontent_v.size() << endl;
  cout << content_v.size() << endl;
  // const
  const ft::vector< int > nocontent_cv(nocontent_v);
  const ft::vector< int > content_cv(content_v);
  cout << nocontent_cv.size() << endl;
  cout << content_cv.size() << endl;
}

void test_max_size() {
  pout("max_size");

  ft::vector< int > v(5, 42);
  cout << v.max_size() << endl;
}

void test_reserve() {
  pout("reserve");

  ft::vector< int > v(5, 42);
  v.reserve(1);
  vdebug(v);
  v.reserve(5);
  vdebug(v);
  v.reserve(100);
  vdebug(v);
}

void test_capacity() {
  pout("capacity");

  ft::vector< int > default_v;
  ft::vector< int > v(5, 42);
  cout << default_v.capacity() << endl;
  cout << v.capacity() << endl;
  // const
  const ft::vector< int > default_cv(default_v);
  const ft::vector< int > cv(v);
  cout << default_cv.size() << endl;
  cout << cv.size() << endl;
}

void test_clear() {
  pout("clear");

  ft::vector< int > default_v;
  ft::vector< int > v(5, 42);
  default_v.clear();
  v.clear();
  vdebug(default_v);
  vdebug(v);
}

void test_insert() {
  pout("insert");

  ft::vector< int > v(base_v);
  ft_intvec_iter it = v.begin();
  it = v.insert(it, 100);
  cout << *it << endl;
  vdebug(v);
  it = v.begin() + 4;
  it = v.insert(it, 200);
  vdebug(v);
  cout << *it << endl;

  // void insert(iterator pos, size_type count, const T& value) {
  //   guacamoleだとokなので一旦コメントアウト
  // it = v.begin() + 4;
  // v.insert(it, 500, 300);
  // vdebug(v);
  // it = v.begin() + 4;
  // v.insert(it, 0, 400);
  // vdebug(v);

  // void insert(iterator pos, InputIterator first, InputIterator last,
  //             typename ft::enable_if< !ft::is_integral< InputIterator
  //             >::value,
  //                                     InputIterator >::type* = NULL);
  std::list< int > list;
  for (int i = 0; i < 5; i++) {
    list.push_back(i * 10);
  }
  std::list< int >::iterator l_it = list.begin();
  std::list< int >::iterator l_ite = list.end();
  l_it++;
  l_ite--;
  it = v.begin() + 4;
  v.insert(it, l_it, l_ite);
  vdebug(v);
}

void test_erase_one() {
  pout("erase_one");
  ft::vector< int > v(base_v);

  ft_intvec_iter it = v.begin() + 1;
  it = v.erase(it);
  vdebug(v);
  cout << *it << endl;
  // stlでcrash
  // it = v.end();
  // it = v.erase(it);
  // vdebug(v);
  // cout << *it << endl;

  // pos が最後の要素を参照する場合は、 end() イテレータが返されます。
  it = --v.end();
  cout << *it << endl;
  it = v.erase(it);
  vdebug(v);
  cout << (it == v.end()) << endl;
}

void test_erase_range() {
  pout("erase_range");
  ft::vector< int > v(base_v);

  ft_intvec_iter it = v.begin() + 1;
  ft_intvec_iter ite = v.begin() + 3;
  it = v.erase(it, ite);
  vdebug(v);
  cout << *it << endl;
  // 削除前に last==end() であった場合は、更新後の end() イテレータが返されます
  ite = v.end();
  it = v.erase(it, ite);
  vdebug(v);
  cout << (*it != *ite) << endl << (*it == *v.end()) << endl;
  // [first, last) が空範囲の場合は、 last が返されます。
  it = v.begin();
  it = v.erase(it, it);
  vdebug(v);
  cout << (it == v.begin()) << endl;
}

void test_erase() {
  test_erase_one();
  test_erase_range();
}

void test_push_back() {
  pout("push_back");
  ft::vector< int > default_v;
  ft::vector< int > v(5, 42);
  default_v.push_back(219);
  v.push_back(219);
  vdebug(default_v);
  vdebug(v);
}

void test_pop_back() {
  pout("pop_back");

  // segv
  // ft::vector< int > default_v;
  //  default_v.pop_back();
  // vdebug(default_v);
  ft::vector< int > v(5, 42);
  v.pop_back();
  vdebug(v);
}

void test_resize() {
  pout("resize");

  ft::vector< int > v(5, 42);
  v.resize(5);
  vdebug(v);
  v.resize(4);
  vdebug(v);
  //   guacamoleだとokなので一旦コメントアウト
  // v.resize(6);
  // vdebug(v);
}

void test_op_compare() {
  pout("op_compare");

  ft::vector< int > v(5, 42);
  ft::vector< int > copy(v);
  ft::vector< int > large_v(v);
  large_v[2] = 43;

  cout << (v == copy) << endl;
  cout << (v != copy) << endl;
  cout << (v < large_v) << endl;
  cout << (v <= large_v) << endl;
  cout << (v <= copy) << endl;
  cout << (large_v >= v) << endl;
  cout << (v >= copy) << endl;
}

void test_swap() {
  pout("swap");

  ft::vector< int > v(5, 42);
  ft::vector< int > v2(2, 21);

  vdebug(v);
  vdebug(v2);
  std::swap(v, v2);
  vdebug(v);
  vdebug(v2);
}

void create_base_vec() {
  for (int i = 0; i < 5; i++) {
    base_v.push_back(i);
  }
}

int main() {
  create_base_vec();

  test_type();
  test_constructor();
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
  // 非メンバ関数
  test_op_compare();
  test_swap();
  ft::vector< int > v2(5, 42);
  // const ft::vector< int > cv2(v2);
  ft::vector< int >::iterator it2 = v2.begin();
  ft::vector< int >::const_iterator cit = v2.begin();
  // ft::vector< int >::const_iterator cit = cv2.begin();
  // std::cout << std::boolalpha;
  cout << (it2 == cit) << endl;
  // ft::reverse_iterator< ft::vector< int >::const_iterator > it1 =
  // v2.rbegin();
  // cout << *(--it1) << endl;
  return 0;
}

// get_allocatorに自作allocator入れる
