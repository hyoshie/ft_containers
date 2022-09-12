#include <algorithm>
#include <exception>
#include <iostream>
#include <list>

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

void tutorial_test() {
  {
    ft::vector< int > v(1);
    // ft::vector<int>::iterator
    ft::vector< int >::iterator i = v.begin();
    // ft_intvec_iter i = v.begin();
    // OK、代入可能
    *i = 0;
    // constなvectorへのリファレンス
    const ft::vector< int >& cv = v;
    // ft::vector<int>::const_iterator ここがとれない
    ft::vector< int >::const_iterator ci = cv.begin();
    // const_iteratorを参照した先には代入できない
    cout << *ci << endl;
  }

  {
    ft::vector< int > v;
    for (int i = 1; i <= 5; ++i) v.push_back(i);

    // イテレーター
    ft_intvec_iter i = v.begin();
    cout << *i << endl;  // 1

    // リバースイテレーター
    ft_intvec_riter r = v.rbegin();
    ft::reverse_iterator< ft::vector< int >::iterator > r2 = v.rbegin();
    cout << *r << endl;   // 5
    cout << *r2 << endl;  // 5
  }
  // {
  //   std::vector< int > v;
  //   for (int i = 1; i <= 5; ++i) v.push_back(i);

  //   // イテレーター
  //   std::vector< int >::iterator i = v.begin();
  //   cout << *i << endl;  // 1

  //   // リバースイテレーター
  //   std::vector< int >::reverse_iterator r = v.rbegin();
  //   // std_intvec_riter r = v.rbegin();
  //   cout << *r << endl;  // 5
  // }
  {
    ft::vector< int > v;
    // true、要素数0
    bool a = v.empty();
    cout << std::boolalpha;
    cout << a << endl;
    v.push_back(0);
    // false、要素数非ゼロ
    bool b = v.empty();
    cout << b << endl;
    // 1、現在の要素数
    size_t s = v.size();
    cout << s << endl;
    // 実装依存、追加の動的メモリー確保をせずに格納できる要素の最大数
    size_t c = v.capacity();
    cout << "size:" << c << endl;
  }

  {
    ft::vector< int > v;
    for (int i = 1; i <= 5; ++i) v.push_back(i);
    v[1];  // 2
    v[3];  // 4
  }

  {
    try {
      // 有効なインデックスはv[0]からv[4]まで
      ft::vector< int > v;
      for (int i = 1; i <= 5; ++i) v.push_back(i);

      v[0] = 0;  // OK
      v[3] = 0;  // OK
      v[5] = 0;  // エラー
    } catch (std::out_of_range& e) {
      cout << e.what();
    }
  }

  {
    ft::vector< int > v;
    for (int i = 1; i <= 5; ++i) v.push_back(i);
    v.front();  // 1
    v.back();   // 5
  }

  {
    ft::vector< int > v;
    cout << v.empty() << endl;  // true
  }

  {
    ft::vector< int > v(100);
    cout << v.size() << endl;  // 100
  }

  {
    ft::vector< int > v(100, 123);
    v[0];   // 123
    v[12];  // 123
    v[68];  // 123
  }

  {
    ft::vector< int > v;
    v.resize(10);
    v.size();  // 10
    // 減らす
    v.resize(5);
    v.size();  // 5
  }

  {
    ft::vector< int > v;
    v.resize(3, 123);
    // vは{123,123,123}
  }

  {
    ft::vector< int > v;
    for (int i = 1; i <= 5; ++i) v.push_back(i);
    v.resize(3);
    // vは{1,2,3}
  }

  {
    ft::vector< int > v;
    // vは{}
    v.push_back(1);
    // vは{1}
    v.push_back(2);
    // vは[1,2}
    v.push_back(3);
    // vは{1,2,3}
  }

  {
    ft::vector< int > v;
    // 少なくとも3個の要素を追加できるように動的メモリー確保
    v.reserve(3);
    v.size();      // 0
    v.capacity();  // 3以上

    // 動的メモリー確保は発生しない
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    // 動的メモリー確保が発生する可能性がある。
    v.push_back(3);
  }

  {
    ft::vector< int > v;
    for (int i = 1; i <= 3; ++i) v.push_back(i);
    v.clear();
    v.size();  // 0
  }

  {
    std::allocator< int > alloc;
    // 空
    ft::vector< int > v1(alloc);
    // 要素数5
    //    ft::vector<int> v2(5, alloc);
    // 要素数5で初期値123
    ft::vector< int > v3(5, 123, alloc);
  }

  {
    // 要素数5
    ft::vector< int > v;
    for (int i = 1; i <= 5; ++i) v.push_back(i);
    // 3個の要素を保持できるよう予約
    v.reserve(3);
    // 無視する
  }

  {
    ft::vector< int > v;
    // おそらく動的メモリー確保
    v.reserve(10000);
  }

  {
    // 要素数3
    ft::vector< int > v;
    for (int i = 1; i <= 3; ++i) v.push_back(i);
    // 1万個の要素を保持できるだけのメモリーを予約
    v.reserve(10000);
    // vは{1,2,3}
  }

  {
    // 要素数0
    ft::vector< int > v;
    // 要素数10
    v.resize(10);
    // 要素数5
    v.resize(5);
    // 要素数変わらず
    v.resize(5);
  }

  {
    ft::vector< int > v;
    for (int i = 1; i <= 3; ++i) v.push_back(i);
    v.resize(5, 4);
    // vは{1,2,3,4,4}
  }

  {
    // 要素数5
    ft::vector< int > v(5);
    v.resize(5);  // 何もしない
  }

  {
    ft::vector< int > v(10, 1);
    v[2] = 99;
    v.resize(5);
    // vは{1,1,99,1,1}
  }

  {
    ft::vector< int > v;
    // vは{}
    v.push_back(1);
    // vは{1}
    v.push_back(2);
    // vは{1,2}
  }

  {
    std::list< int > l(5, 42);
    ft::vector< int > v(l.begin(), l.end());
    // vは{1,2,3,4,5}
  }

  {
    ft::vector< int > v;
    for (int i = 1; i <= 5; ++i) {
      v.push_back(i);
    }
    ft::vector< int > w = v;
    // wは{1,2,3,4,5}
  }
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

// void test_reserve() {
//   pout("reserve");

//   ft::vector< int > default_v;
//   ft::vector< int > alloc_v(allocator);
//   ft::vector< int > value_v(5, 219);
//   ft::vector< int > iter_v(list.begin(), list.end());
//   ft::vector< int > copy_v(value_v);
//   vdebug(default_v);
//   vdebug(alloc_v);
//   vdebug(value_v);
//   vdebug(iter_v);
//   vdebug(copy_v);
// }

int main() {
  // tutorial_test();
  test_constructor();
  test_op_equal();
  // test_assign();
  // test_getallocator();
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
  // test_maxsize();
  // test_reserve();
  // 変更
  return 0;
}
