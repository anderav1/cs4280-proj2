// Lexi Anderson
// CS4280, Proj 2
// testTree.cpp

#include <iomanip>
#include <iostream>

#include "node.h"
#include "testTree.h"


// Traverse the tree in pre-order and print each node
void printTree(node_t* root, int depth) {
  if (root == nullptr) return;
  
  printNode(root, depth);
  
  printTree(root->ch1, depth + 1);
  printTree(root->ch2, depth + 1);
  printTree(root->ch3, depth + 1);
  printTree(root->ch4, depth + 1);
  printTree(root->ch5, depth + 1);
  printTree(root->ch6, depth + 1);
  printTree(root->ch7, depth + 1);
}

// Print node with indentation appropriate to its depth in the tree
void printNode(node_t* node, int depth) {
  std::cout << std::setw(depth * 4) << " " << node->label;
  std::cout << std::setw(1) << " " << node->decor << std::endl;
}
