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
#define LOOP_CNT 2000000
#define BASE_SIZE 250000

#include <cstdio>

double buff[LOOP_CNT];

void test_tree2(void) {
  for (int n = BASE_SIZE; n <= LOOP_CNT; n *= 2) {
    BinarySearchTree *tree = new BinarySearchTree;
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
