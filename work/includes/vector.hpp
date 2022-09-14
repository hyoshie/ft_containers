#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <limits>
#include <memory>
#include <stdexcept>

#include "iterator.hpp"
#include "util.hpp"

namespace ft {
template < typename T, typename Allocator = std::allocator< T > >
class vector {
 public:
  // ネストされた型名
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename ft::random_access_iterator< value_type > iterator;
  typedef typename ft::random_access_iterator< const value_type >
      const_iterator;
  typedef typename ft::reverse_iterator< iterator > reverse_iterator;
  typedef typename ft::reverse_iterator< const_iterator >
      const_reverse_iterator;

  // コンストラクター
  vector()
      : first_(NULL),
        last_(NULL),
        reserved_last_(NULL),
        alloc_(allocator_type()) {}

  explicit vector(const allocator_type& alloc)
      : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc) {}

  explicit vector(size_type size, const T& value = T(),
                  const allocator_type& alloc = allocator_type())
      : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc) {
    reserve(size);
    for (; last_ != reserved_last_; ++last_) {
      construct(last_, value);
    }
  }

  template < typename InputIterator >
  vector(InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type(),
         typename ft::enable_if< !ft::is_integral< InputIterator >::value,
                                 InputIterator >::type* = NULL)
      : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc) {
    reserve(std::distance(first, last));
    for (InputIterator i = first; i != last; ++i) {
      push_back(*i);
    }
  }

  // デストラクター
  ~vector() {
    clear();
    deallocate();
  }
  // コピー
  vector(const vector& rhs)
      : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(rhs.alloc_) {
    reserve(rhs.size());
    pointer dest = first_;
    for (const_iterator src = rhs.begin(), last = rhs.end(); src != last;
         ++dest, ++src) {
      construct(dest, *src);
    }
    last_ = first_ + rhs.size();
  }
  vector& operator=(const vector& rhs) {
    if (this == &rhs) {
      return *this;
    }
    if (size() == rhs.size()) {
      std::copy(rhs.begin(), rhs.end(), begin());
    } else {
      if (capacity() >= rhs.size()) {
        destroy_until(rend());
        for (const_iterator src_iter = rhs.begin(),
                            src_end = rhs.begin() + rhs.size();
             src_iter != src_end; ++src_iter, ++last_) {
          construct(last_, *src_iter);
        }
      } else {
        destroy_until(rend());
        reserve(rhs.size());
        for (const_iterator src_iter = rhs.begin(), src_end = rhs.end();
             src_iter != src_end; ++src_iter, ++last_) {
          construct(last_, *src_iter);
        }
      }
    }
    return *this;
  }

  void assign(size_type count, const T& value) {
    if (count > capacity()) {
      clear();
      deallocate();
      first_ = allocate(count);
      last_ = first_;
      reserved_last_ = first_ + count;
      for (; last_ != reserved_last_; ++last_) {
        construct(last_, value);
      }
    } else {
      clear();
      last_ = first_;
      for (size_type i = 0; i < count; ++i, ++last_) {
        construct(last_, value);
      }
    }
  }

  template < class InputIt >
  void assign(InputIt first, InputIt last,
              typename ft::enable_if< !ft::is_integral< InputIt >::value,
                                      InputIt >::type* = NULL)

  {
    size_type count = std::distance(first, last);
    if (count > capacity()) {
      clear();
      deallocate();
      first_ = allocate(count);
      last_ = first_;
      reserved_last_ = first_ + count;
      for (; last_ != reserved_last_; ++last_, ++first) {
        construct(last_, *first);
      }
    } else {
      clear();
      last_ = first_;
      for (size_type i = 0; i < count; ++i, ++last_, ++first) {
        construct(last_, *first);
      }
    }
  }

  allocator_type get_allocator() const { return alloc_; }

  // 要素アクセス
  reference operator[](size_type i) { return first_[i]; }
  const_reference operator[](size_type i) const { return first_[i]; }
  reference at(size_type i) {
    if (i >= size()) throw std::out_of_range("index is out of range.");
    return first_[i];
  }
  const_reference at(size_type i) const {
    if (i >= size()) throw std::out_of_range("index is out of range.");
    return first_[i];
  }
  reference front() { return *first_; }
  const_reference front() const { return *first_; }
  reference back() { return *(last_ - 1); }
  const_reference back() const { return *(last_ - 1); }

  // イテレーターアクセス
  iterator begin() { return iterator(first_); }
  const_iterator begin() const { return const_iterator(first_); }
  iterator end() { return iterator(last_); }
  const_iterator end() const { return const_iterator(last_); }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  // 容量
  size_type size() const { return size_type(last_ - first_); }

  bool empty() const { return begin() == end(); }

  size_type capacity() const { return std::distance(first_, reserved_last_); }

  void reserve(size_type sz) {
    if (sz <= capacity()) return;
    // 古いストレージの情報を保存
    pointer ptr = allocate(sz);
    pointer old_first = first_;
    pointer old_last = last_;
    size_type old_capacity = capacity();
    // 新しいストレージに差し替え
    first_ = ptr;
    last_ = first_;
    reserved_last_ = first_ + sz;
    // 古いストレージから新しいストレージに要素をコピー構築
    for (pointer old_iter = old_first; old_iter != old_last;
         ++old_iter, ++last_) {
      construct(last_, *old_iter);
    }
    // 古いストレージの値を破棄
    for (reverse_iterator riter = reverse_iterator(iterator(old_last)),
                          rend = reverse_iterator(iterator(old_first));
         riter != rend; ++riter) {
      destroy(&*riter);
    }
    alloc_.deallocate(old_first, old_capacity);
  }

  size_type max_size() const {
    return std::min< size_type >(alloc_.max_size(),
                                 std::numeric_limits< difference_type >::max());
  }

  // 変更
  void clear() { destroy_until(rend()); }

  iterator insert(iterator pos, const T& value) {
    size_type offset = pos - begin();
    insert(pos, 1, value);
    return begin() + offset;
  }

  void insert(iterator pos, size_type count, const T& value) {
    size_type offset = pos - begin();
    size_type new_size = size() + count;

    expand_capacity(new_size);
    for (pointer new_last = first_ + new_size; last_ != new_last; ++last_) {
      construct(last_);
    }
    iterator it = begin() + offset;
    move_elements(it, count);
    for (size_type i = 0; i < count; i++, it++) {
      *it = value;
    }
  }

  template < class InputIterator >
  void insert(iterator pos, InputIterator first, InputIterator last,
              typename ft::enable_if< !ft::is_integral< InputIterator >::value,
                                      InputIterator >::type* = NULL) {
    size_type offset = std::distance(begin(), pos);
    size_type count = std::distance(first, last);
    size_type new_size = size() + count;

    expand_capacity(new_size);
    for (pointer new_last = first_ + new_size; last_ != new_last; ++last_) {
      construct(last_);
    }
    iterator it = begin() + offset;
    move_elements(it, count);
    for (; first != last; first++, it++) {
      *it = *first;
    }
  }

  iterator erase(iterator pos) {
    size_type offset = std::distance(begin(), pos);
    move_elements_backward(pos, 1);
    destroy(--last_);
    return begin() + offset;
  }

  iterator erase(iterator first, iterator last) {
    size_type offset = std::distance(begin(), first);
    size_type count = std::distance(first, last);

    if (first == last) {
      return last;
    }
    move_elements_backward(first, count);
    for (size_type i = 0; i < count; i++) {
      destroy(--last_);
    }
    return begin() + offset;
  }

  void push_back(const T& value) {
    if (size() + 1 > capacity()) {
      size_type c = size();
      if (c == 0) {
        c = 1;
      } else {
        c *= 2;  //オーバーフロー処理
      }
      reserve(c);
    }
    construct(last_, value);
    ++last_;
  }

  void pop_back() { destroy(--last_); }

  void resize(size_type sz, T value = T()) {
    if (sz < size()) {
      size_type diff = size() - sz;
      destroy_until(rbegin() + diff);
      last_ = first_ + sz;
    } else if (sz > size()) {
      insert(end(), sz - size(), value);
    }
  }

  void swap(vector& other) {
    swap_data(first_, other.first_);
    swap_data(last_, other.last_);
    swap_data(reserved_last_, other.reserved_last_);
  }

 private:
  pointer allocate(size_type n) { return alloc_.allocate(n); }

  void deallocate() { alloc_.deallocate(first_, capacity()); }

  void construct(pointer ptr) { alloc_.construct(ptr, T()); }

  void construct(pointer ptr, const T& value) { alloc_.construct(ptr, value); }

  void destroy(pointer ptr) { alloc_.destroy(ptr); }

  void destroy_until(reverse_iterator rend) {
    for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last_) {
      destroy(&*riter);  // ?
    }
  }

  void move_elements(iterator first, size_type offset) {
    reverse_iterator end = reverse_iterator(first);
    reverse_iterator src = reverse_iterator(iterator(last_ - offset));
    reverse_iterator dst = rbegin();
    for (; src != end; src++, dst++) {
      *dst = *src;
    }
  }

  void move_elements_backward(iterator first, size_type offset) {
    iterator src = first + offset;
    iterator dst = first;
    for (; src != end(); src++, dst++) {
      *dst = *src;
    }
  }

  void expand_capacity(size_type sz) {
    if (sz <= capacity()) {
      return;
    }
    size_type c = capacity();
    while (sz > c) {
      if (c == 0) {
        c = 1;
      } else {
        c *= 2;  //オーバーフロー処理
      }
    }
    reserve(c);
  }

  template < typename U >
  void swap_data(U& lhs, U& rhs) {
    U tmp = lhs;
    lhs = rhs;
    rhs = tmp;
  }

  pointer first_;
  pointer last_;
  pointer reserved_last_;
  allocator_type alloc_;
};

template < class T, class Alloc >
bool operator==(const ft::vector< T, Alloc >& lhs,
                const ft::vector< T, Alloc >& rhs) {
  return (lhs.size() == rhs.size()) &&
         ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template < class T, class Alloc >
bool operator!=(const ft::vector< T, Alloc >& lhs,
                const ft::vector< T, Alloc >& rhs) {
  return !(lhs == rhs);
}

template < class T, class Alloc >
bool operator<(const ft::vector< T, Alloc >& lhs,
               const ft::vector< T, Alloc >& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template < class T, class Alloc >
bool operator<=(const ft::vector< T, Alloc >& lhs,
                const ft::vector< T, Alloc >& rhs) {
  return !(lhs > rhs);
}

template < class T, class Alloc >
bool operator>(const ft::vector< T, Alloc >& lhs,
               const ft::vector< T, Alloc >& rhs) {
  return rhs < lhs;
}

template < class T, class Alloc >
bool operator>=(const ft::vector< T, Alloc >& lhs,
                const ft::vector< T, Alloc >& rhs) {
  return !(lhs < rhs);
}

}  // namespace ft

namespace std {
template < class T, class Alloc >
void swap(ft::vector< T, Alloc >& lhs, ft::vector< T, Alloc >& rhs) {
  lhs.swap(rhs);
}

}  // namespace std

#endif /* VECTOR_HPP */
