#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>

namespace ft {
template <typename T, typename Allocator = std::allocator<T> >
class vector {
 public:
  // ネストされた型名
  using value_type = T;
  using allocator_type = Allocator;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // コンストラクター
  vector() : vector(allocator_type()) {}
  vector(const allocator_type &alloc) noexcept : alloc_(alloc) {}
  vector(size_type size, const allocator_type &alloc) noexcept : alloc_(alloc) {
    resize(size);
  }
  vector(size_type size, const_reference value,
         const allocator_type &alloc) noexcept
      : alloc_(alloc) {
    resize(size, value);
  }
  // デストラクター
  ~vector() {
    clear();
    deallocate();
  }
  // コピー
  vector(const vector &x);
  vector &operator=(const vector &x);

  // 要素アクセス
  void push_back(const T &x);
  reference operator[](size_type i) noexcept { return first_[i]; }
  const_reference operator[](size_type i) const noexcept { return first_[i]; }
  reference at(size_type i) noexcept {
    if (i >= size()) throw std::out_of_range("index is out of range.");
    return first_[i];
  }
  const_reference &at(size_type i) const noexcept {
    if (i >= size()) throw std::out_of_range("index is out of range.");
    return first_[i];
  }

  // イテレーターアクセス
  iterator begin() noexcept { return first_; }
  iterator begin() const noexcept { return first_; }
  const_iterator cbegin() const noexcept { return first_; }
  iterator end() noexcept { return last_; }
  iterator end() const noexcept { return last_; }
  const_iterator cend() const noexcept { return end; }
  iterator rbegin() noexcept { return reverse_iterator{last_}; }
  iterator rbegin() const noexcept { return reverse_iterator{last_}; }
  const_reverse_iterator crbegin() const noexcept {
    return reverse_iterator{last_};
  }
  iterator rend() noexcept { return reverse_iterator{first_}; }
  iterator rend() const noexcept { return reverse_iterator{first_}; }
  const_reverse_iterator crend() const noexcept {
    return reverse_iterator{last_};
  }

  // 容量
  size_type size() const noexcept { return std::distance(begin(), end()); }
  bool empty() const noexcept { return begin() == end(); }
  size_type capacity() const noexcept {
    return std::distance(first_, reserved_last_);
  }
  size_type capacity() const noexcept {
    return std::distance(first_, reserved_last_);
  }

  // 変更
  void clear() noexcept { destroy_until(rend()); }

 private:
  using traits = std::allocator_traits<allocator_type>;

  pointer allocate(sizetype n) { return traits::allocate(alloc, n); }
  pointer deallocate(sizetype n) {
    return traits::deallocate(alloc, n, capacity());
  }
  void construct(pointer ptr) { traits::construct(allco, ptr); }
  void construct(pointer ptr, const_reference value) {
    traits::construct(alloc, ptr, value);
  }
  // void construct(pointer ptr, value_type &&value) {
  //   traits::construct(allco, ptr, std::move(value));
  // }
  void destroy(pointer ptr) { traits::destroy(alloc, ptr); }
  void destroy_until(reverse_iterator rend) {
    for (auto riter = rbegin(); riter != rend; ++riter, --last) {
      destroy(&*riter);  // ?
    }
  }

  pointer first_;
  pointer last_;
  pointer reserved_last_;
  allocator_type alloc_;
};

}  // namespace ft

#endif /* VECTOR_HPP */
