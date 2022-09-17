#include <iostream>
#include <vector>

#include "tree.hpp"

void test_tree() {
  BinarySearchTree btree;

  std::cout << std::boolalpha;
  std::cout << btree.add(10) << std::endl;
  std::cout << btree.add(2) << std::endl;
  std::cout << btree.add(3000) << std::endl;
  std::cout << btree.add(450) << std::endl;
  std::cout << btree.add(-5) << std::endl;
  std::cout << btree.add(8) << std::endl;
  std::cout << std::boolalpha << "search(450):" << (btree.search(450) != NULL)
            << std::endl;
  std::cout << std::boolalpha << "search(451):" << (btree.search(451) != NULL)
            << std::endl;

  btree.remove(btree.search(450));
  btree.print_all();
  std::cout << "depth:" << depth(btree.root()) << std::endl;
  std::cout << "size:" << size(btree.root()) << std::endl;
  std::cout << "height:" << height(btree.root()) << std::endl;
}
