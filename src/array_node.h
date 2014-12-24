#ifndef ARRAY_NODE_H
#define ARRAY_NODE_H

#include "node.h"
#include "tree.h"

/**
 * Node implementation that creates an array of alphabet_size in each Node to
 * store links to its children.
 * Each node is O(alphabet_size) in memory.
 */
class ArrayNode : public Node {
  public:

    ArrayNode(const Tree *tree, int edge_start, int edge_end);

    ~ArrayNode() {
      delete[] next_;
    }

    void set(int t, Node* node) {
      next_[t] = node;
    }

    Node * operator[] (int i) const {
      return next_[i];
    }

    void delete_subtree();

  private:
    Node **next_;
};

#endif
