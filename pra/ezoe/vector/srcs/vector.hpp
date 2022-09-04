#ifndef VECTOR_HPP
#define VECTOR_HPP

// #include <experimental/scope>
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
  vector(size_type size,
         const allocator_type &alloc = allocator_type()) noexcept
      : vector(alloc) {
    resize(size);
  }
  vector(size_type size, const_reference value,
         const allocator_type &alloc = allocator_type()) noexcept
      : vector(alloc) {
    resize(size, value);
  }
  // enable_if
  // template <typename InputIterator>
  // vector(InputIterator first, InputIterator last,
  //        const allocator_type &alloc = allocator_type()) {
  //   reserve(std::distance(first, last));
  //   for (auto i = first; i != last; ++i) {
  //     push_back(i);
  //   }
  // }
  // vector(std::initializer_list<value_type> init,
  //        const allocator_type &alloc = allocator_type())
  //     : vector(init.begin(), init.end(), alloc) {}

  // デストラクター
  ~vector() {
    clear();
    deallocate();
  }
  // コピー
  vector(const vector &rhs)
      : alloc_(traits::select_on_container_copy_construction(rhs.alloc_)) {
    reserve(rhs.size());
    for (auto dest = first_, src = rhs.begin(), last = rhs.end(); src != last;
         ++dest, ++src) {
      construct(dest, *src);
    }
    last_ = first_ + rhs.size();
  }
  vector &operator=(const vector &rhs) {
    if (this == &rhs) {
      return *this;
    }
    if (size() == rhs.size()) {
      std::copy(rhs.begin(), rhs.end(), begin());
    } else {
      if (capacity() >= rhs.size()) {
        std::copy(rhs.begin(), rhs.begin() + rhs.size(), begin());
        for (auto src_iter = rhs.begin() + rhs.size(), src_end = rhs.end();
             src_iter != src_end; ++src_iter, ++last_) {
          construct(last_, *src_iter);
        }
      } else {
        destroy_until(rend());
        reserve(rhs.size());
        for (auto src_iter = rhs.begin(), src_end = rhs.end(),
                  dest_iter = begin();
             src_iter != src_end; ++src_iter, ++dest_iter, ++last_) {
          construct(dest_iter, *src_iter);
        }
      }
    }
    return *this;
  }

  // 要素アクセス
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
  reverse_iterator rbegin() noexcept { return reverse_iterator{last_}; }
  reverse_iterator rbegin() const noexcept { return reverse_iterator{last_}; }
  const_reverse_iterator crbegin() const noexcept {
    return reverse_iterator{last_};
  }
  reverse_iterator rend() noexcept { return reverse_iterator{first_}; }
  reverse_iterator rend() const noexcept { return reverse_iterator{first_}; }
  const_reverse_iterator crend() const noexcept {
    return reverse_iterator{last_};
  }

  // 容量
  size_type size() const noexcept { return std::distance(begin(), end()); }
  bool empty() const noexcept { return begin() == end(); }
  size_type capacity() const noexcept {
    return std::distance(first_, reserved_last_);
  }
  void reserve(size_type sz) {
    if (sz <= capacity()) return;
    // 古いストレージの情報を保存
    auto ptr = allocate(sz);
    auto old_first = first_;
    auto old_last = last_;
    // auto old_capacity = capacity();
    // 新しいストレージに差し替え
    first_ = ptr;
    last_ = first_;
    reserved_last_ = first_ + sz;
    // 例外安全のため
    // 信託すエラーになるのでコメントアウト
    // std::scope_exit e(
    //     [&] { traits::deallocate(alloc_, old_first, old_capacity); });
    // 古いストレージから新しいストレージに要素をコピー構築
    // 実際にはmove構築
    for (auto old_iter = old_first; old_iter != old_last; ++old_iter, ++last_) {
      construct(last_, std::move(*old_iter));
    }
    // 古いストレージの値を破棄
    for (auto riter = reverse_iterator(old_last),
              rend = reverse_iterator(old_first);
         riter != rend; ++riter) {
      destroy(&*riter);
    }
  }

  // 変更
  void clear() noexcept { destroy_until(rend()); }
  void resize(size_type sz) {
    if (sz < size()) {
      auto diff = size() - sz;
      destroy_until(rbegin() + diff);
      last_ = first_ + sz;
    } else if (sz > size()) {
      reserve(sz);
      for (; last_ != reserved_last_; ++last_) {
        construct(last_);
      }
    }
  }
  void resize(size_type sz, const_reference value) {
    if (sz < size()) {
      auto diff = size() - sz;
      destroy_until(rbegin() + diff);
      last_ = first_ + sz;
    } else if (sz > size()) {
      reserve(sz);
      for (; last_ != reserved_last_; ++last_) {
        construct(last_, value);
      }
    }
  }
  void push_back(const_reference value) {
    if (size() + 1 > capacity()) {
      auto c = size();
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
  void shrink_to_fit() {
    if (size() == capacity()) return;
    auto ptr = allocate(size());
    auto current_size = size();
    for (auto raw_ptr = ptr, iter = begin(), iter_end = end(); iter != iter_end;
         ++iter, ++raw_ptr) {
      construct(raw_ptr, *iter);
    }
    clear();
    deallocate();
    first_ = ptr;
    last_ = ptr + current_size;
    reserved_last_ = last_;
  }

 private:
  using traits = std::allocator_traits<allocator_type>;

  pointer allocate(size_type n) { return traits::allocate(alloc_, n); }
  void deallocate() { traits::deallocate(alloc_, first_, capacity()); }
  void construct(pointer ptr) { traits::construct(alloc_, ptr); }
  void construct(pointer ptr, const_reference value) {
    traits::construct(alloc_, ptr, value);
  }
  void construct(pointer ptr, value_type &&value) {
    traits::construct(alloc_, ptr, std::move(value));
  }
  void destroy(pointer ptr) { traits::destroy(alloc_, ptr); }
  void destroy_until(reverse_iterator rend) {
    for (auto riter = rbegin(); riter != rend; ++riter, --last_) {
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
