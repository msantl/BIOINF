#ifndef HASHMAP_NODE_H
#define HASHMAP_NODE_H

#include <unordered_map>

#include "node.h"
#include "tree.h"

/**
 * Node implementation that creates a hashmap from transition letter to node
 * Each node is O(number_of_transitions) in memory.
 */
class HashmapNode : public Node {
  public:

    HashmapNode(const Tree *tree, int edge_start, int edge_end);

    ~HashmapNode() {
      delete next_;
    }

    void set(int t, Node* node) {
      init();
      (*next_)[t] = node;
    }

    Node * operator[] (int i) const {
      if (next_ == NULL) return NULL;
      auto next_node = next_->find(i);
      if (next_node != next_->end()) return next_node->second;
      return NULL;
    }

    void delete_subtree();

  private:
    std::unordered_map<int, Node*> *next_;

    void init() {
      if (next_ == NULL) {
        next_ = new std::unordered_map<int, Node*>();
      }
    }
};

#endif
