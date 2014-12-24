#include "array_node.h"

ArrayNode::ArrayNode(const Tree *tree, int edge_start, int edge_end)
  : Node(tree, edge_start, edge_end) {
  this->next_ = new Node*[tree->alphabet_size];
  for (int i = 0; i < tree->alphabet_size; i++) {
    next_[i] = NULL;
  }
}

void ArrayNode::delete_subtree() {
  for (int i = 0; i < tree_->alphabet_size; i++) {
    if ((*this)[i] != NULL) (*this)[i]->delete_subtree();
    delete (*this)[i];
  }
}
