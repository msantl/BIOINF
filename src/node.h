#ifndef NODE_H
#define NODE_H

#include <cstddef>

class Tree;

/**
 * Abstract base class for all nodes.
 */
class Node {
  public:
    const Tree *tree_;
    /**
     * Information about edge from parent to this node.
     * text[edge_start...edge_end]
     * edge_end == -1 => signifies the end of the current text
     */
    int edge_start_, edge_end_;
    Node *suffix_link_;

    Node(const Tree *tree, int edge_start, int edge_end)
      : tree_(tree),
      edge_start_(edge_start),
      edge_end_(edge_end),
      suffix_link_(NULL) {}

    virtual ~Node() {};

    /**
     * Sets node to be the t-transition from this node.
     */
    virtual void set(int t, Node* node) = 0;

    /**
     * Retrieves a node we go to by using transition t.
     */
    virtual Node * operator[] (int t) const = 0;

    /**
     * Deletes every node in a subtree of this node, except this one.
     */
    virtual void delete_subtree() = 0;

    /**
     * Computes edge length to its parent.
     */
    int edge_length() const;
};

#endif
