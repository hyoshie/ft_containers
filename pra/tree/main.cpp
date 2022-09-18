#include <iostream>
#include <vector>

#include "BinarySearchTree.hpp"

void test_tree() {
  BinarySearchTree< double > btree;

  // std::cout << std::boolalpha << btree.add(44) << std::endl
  //           << btree.add(2) << std::endl
  //           << btree.add(3000) << std::endl
  //           << btree.add(450) << std::endl
  //           << btree.add(-5) << std::endl
  //           << btree.add(8) << std::endl;
  double array[] = {5, 8, 2, 7, 10, 9, 3, 6, 4, 1};

  for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
    btree.add(array[i]);
  }

  std::cout << std::boolalpha << "search(450):" << (btree.search(450) != NULL)
            << std::endl;
  std::cout << std::boolalpha << "search(451):" << (btree.search(451) != NULL)
            << std::endl;

  btree.remove(btree.search(450));
  btree.print_all();
  // pre_order_print(btree.root());
  // in_order_print(btree.root());
  // post_order_print(btree.root());
  std::cout << "depth:" << depth(btree.root()) << std::endl;
  std::cout << "size:" << size(btree.root()) << std::endl;
  std::cout << "height:" << height(btree.root()) << std::endl;
}

#define LOOP_CNT 2000000
#define BASE_SIZE 250000

#include <cstdio>

double buff[LOOP_CNT];

void test_tree2(void) {
  for (int n = BASE_SIZE; n <= LOOP_CNT; n *= 2) {
    BinarySearchTree< double > *tree = new BinarySearchTree< double >;
    srand(time(NULL) + n);
    for (int i = 0; i < n; i++) buff[i] = rand();
    std::cout << "----- " << n << " -----\n";
    clock_t s = clock();
    for (int i = 0; i < n; i++) tree->add(buff[i]);
    printf("挿入時間 %.3f\n", (double)(clock() - s) / CLOCKS_PER_SEC);
    printf("高さ %d\n", height(tree->root()));
    std::cout << "ノード数:" << size(tree->root()) << std::endl;
    s = clock();
    for (int i = 0; i < n; i++)
      if (!tree->search(buff[i])) fprintf(stderr, "search error\n");
    printf("探索時間 %.3f\n", (double)(clock() - s) / CLOCKS_PER_SEC);
    s = clock();
    for (int i = 0; i < n; i++) tree->remove(tree->search(buff[i]));
    printf("探索+削除時間 %.3f\n", (double)(clock() - s) / CLOCKS_PER_SEC);
    delete tree;
  }
}

int main() {
  test_tree();
  // test_tree2();
}
