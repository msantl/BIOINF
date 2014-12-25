#include "hashmap_node.h"

using namespace std;

HashmapNode::HashmapNode(const Tree *tree, int edge_start, int edge_end)
  : Node(tree, edge_start, edge_end) {
  next_ = NULL; // unordered_map<int, Node*>();
}

void HashmapNode::delete_subtree() {
  for (int i = 0; i < tree_->alphabet_size; i++) {
    if ((*this)[i] != NULL) (*this)[i]->delete_subtree();
    delete (*this)[i];
  }
}
