// Lexi Anderson
// CS4280, Proj 2
// node.h

#ifndef NODE_H
#define NODE_H

#include "token.h"

typedef struct node_t {
  char label;
  token_t *tkn1 = nullptr, *tkn2 = nullptr, *tkn3 = nullptr, *tkn4 = nullptr;
  node_t *child1 = nullptr, *child2 = nullptr, *child3 = nullptr;
} node_t;

typedef struct {
  node_t *root;
} tree_t;


#endif
