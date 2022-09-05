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

#endif /* ITERATOR_HPP */
