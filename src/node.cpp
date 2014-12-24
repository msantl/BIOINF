#include "node.h"
#include "tree.h"

int Node::edge_length() const {
  if (edge_end_ == Tree::INF) return tree_->text.size() - edge_start_;
  return edge_end_ - edge_start_ + 1;
}

