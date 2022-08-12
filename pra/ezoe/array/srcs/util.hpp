#ifndef UTIL_HPP
#define UTIL_HPP

template <typename Container>
void print(Container const& c) {
  for (std::size_t i = 0; i < c.size(); i++) {
    std::cout << c[i];
  }
}

#endif /* UTIL_HPP */
