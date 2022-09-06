#ifndef ITERATOR_HPP
#define ITERATOR_HPP

struct cout_iterator {
  //---ボイラープレートコード
  using difference_type = void;
  using value_type = void;
  using reference = void;
  using pointer = void;
  using iterator_category = std::output_iterator_tag;
  cout_iterator& operator*() { return *this; }
  cout_iterator& operator++() { return *this; }
  cout_iterator& operator++(int) { return *this; }
  //---ボイラープレートコード

  template <typename T>
  cout_iterator& operator=(T const& x) {
    std::cout << x;
    return *this;
  }
};

template <typename Container>
struct back_inserter {
  back_inserter(Container& c) : c_(c) {}
  //---ボイラープレートコード
  using difference_type = void;
  using value_type = void;
  using reference = void;
  using pointer = void;
  using iterator_category = std::output_iterator_tag;
  back_inserter& operator*() { return *this; }
  back_inserter& operator++() { return *this; }
  back_inserter& operator++(int) { return *this; }
  //---ボイラープレートコード

  back_inserter& operator=(const typename Container::value_type& value) {
    c_.push_back(value);
    return *this;
  }

  Container& c_;
};

template <typename T>
struct cin_iterator {
  //---ボイラープレートコード
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using iterator_category = std::input_iterator_tag;
  //---ボイラープレートコード
  cin_iterator(bool fail = false) : fail_(fail) { ++*this; }
  // referenceだとエラー
  const T& operator*() const { return value_; }
  cin_iterator& operator++() {
    if (!fail_) {
      std::cin >> value_;
      fail_ = std::cin.fail();
    }
    return *this;
  }
  cin_iterator operator++(int) {
    auto old = *this;
    ++*this;
    return old;
  }

  bool fail_;
  value_type value_;
};

template <typename T>
bool operator==(cin_iterator<T> const& l, cin_iterator<T> const& r) {
  return l.fail_ == r.fail_;
}

template <typename T>
bool operator!=(cin_iterator<T> const& l, cin_iterator<T> const& r) {
  return !(l == r);
}

template <typename T>
struct iota_iterator {
  //---ボイラープレートコード
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using iterator_category = std::forward_iterator_tag;
  //---ボイラープレートコード
  iota_iterator(value_type value = 0) : value_(value) {}
  // referenceだとエラー
  reference operator*() noexcept { return value_; }
  const_reference operator*() const noexcept { return value_; }
  iota_iterator& operator++() noexcept {
    ++value_;
    return *this;
  }
  iota_iterator operator++(int) noexcept {
    auto old = *this;
    ++*this;
    return old;
  }
  iota_iterator& operator--() noexcept {
    --value_;
    return *this;
  }
  iota_iterator operator--(int) noexcept {
    auto old = *this;
    --*this;
    return old;
  }
  bool operator==(iota_iterator const& i) const noexcept {
    return value_ == i.value_;
  }
  bool operator!=(iota_iterator const& i) const noexcept {
    return !(*this == i);
  }

  value_type value_;
};

#endif /* ITERATOR_HPP */
