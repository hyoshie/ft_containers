#include <iostream>
#include <vector>

#include "BinarySearchTree.hpp"

void test_tree() {
  BinarySearchTree< int > btree;
  // int array[] = {5, 8, 2, 7, 10, 9, 3, 6, 4, 1};
  int array[] = {2, 9, 8, 7, 10, 6, 3, 5, 4, 1};

  for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
    btree.add(array[i]);
  }

  std::cout << std::boolalpha << "search(10):" << (btree.search(10) != NULL)
            << std::endl;
  std::cout << std::boolalpha << "search(11):" << (btree.search(11) != NULL)
            << std::endl;

  // btree.remove(btree.search(10));
  Node< int > *root = btree.root();
  print_graph(
      root,
      0);  // std::cout << "depth     :" << depth(root) << std::endl; std::cout
           // << "size_re   :" << size(root) << std::endl; std::cout << "height
           // :" << height(root) << std::endl; std::cout << "heightnore:" <<
           // height_no_recursive(root) << std::endl;
}

#define LOOP_CNT 4000000
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

void test_traverse() {
  BinarySearchTree< int > btree;
  double array[] = {5, 8, 2, 7, 10, 9, 3, 6, 4, 1};

  for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
    btree.add(array[i]);
  }

  Node< int > *root = btree.root();
  // btree.print_all();
  pre_order_print(root);
  // in_order_print(root);
  // in_order_print_nore(root);
  // post_order_print(root);
  // post_order_print_nore(root);
  // post_order_print_nore(root->right);
  // print_graph(root, 0);
}

void test_is_balanced() {
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
    for (int i = 0; i < n; i++) is_balanced(tree->search(buff[i]));
    printf("is_balanced %.3f\n", (double)(clock() - s) / CLOCKS_PER_SEC);
    delete tree;
  }
}

int main() {
  // test_tree();
  // test_tree2();
  // test_traverse();
  test_is_balanced();
}
