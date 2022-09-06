#ifndef UTIL_HPP
#define UTIL_HPP

template <typename Container>
void print(Container const& c) {
  for (std::size_t i = 0; i < c.size(); i++) {
    std::cout << c[i];
  }
  std::cout << std::endl;
}

template <typename InputIterator>
void print(InputIterator iter, InputIterator end_iter) {
  while (iter != end_iter) std::cout << *iter++;
  std::cerr << std::endl;
}

#endif /* UTIL_HPP */
