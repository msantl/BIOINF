#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>

class Node;

/**
 * Creates suffix tree in linear time and space.
 * It is based on Algorithm from Esko Ukonnen's paper:
 * On-line construction of suffix trees.
 *
 * It also provides string representation of Tree using dot language.
 */
class Tree {
  public:
    const static int INF = -2;

    std::vector <int> text;
    int alphabet_size;

    /**
     * Creates an empty suffix tree with alphabet in range [0, alphabet_size>.
     */
    Tree(int alphabet_size);

    ~Tree();

    /**
     * Add letter t to the suffix tree.
     * Suffix tree is valid after each insertion.
     */
    void add_transition(int t);

    /**
     * Returns true if string x is in this tree.
     * Elements in string are interpreted as integers by subtracting 'a' from
     * them.
     */
    bool find(const std::string& x);

    /**
     * Creates a representation of tree in dot language.
     */
    std::string toDot();

  private:

    Node *start; // all edges from starta go to root
    Node *root;

    Node *active_node;
    int active_start, active_end;

    /**
     * Makes state (x, (l, r)) explicit and return that state.
     * x - is an explicit state
     * l and r represent substring text[l..r]
     * t - next letter
     * This means, start from node x and spell out the given substring.
     *
     * If the state is already explicit then that state is returned (new state
     * isn't created).
     * If the state is end state, NULL is returned.
     */
    Node* split(Node *x, int l, int r, int t);

    /**
     * Returns canonized state which is corresponds to the one givven in params.
     * r is not returned because it never changes.
     */
    std::pair <Node*, int> canonize(Node *x, int l, int r);

    /**
     * It traverses the tree and writes it to out in a dot format.
     */
    void dfs(const Node *x, int& curr_id, std::ostream& out);

    /**
     * Returns transition string on edge x[t].
     */
    std::string transition(const Node *x, int t);

    /**
     * Helper function that computes how many characters on edge to node and in
     * substring x[x_start:end].
     */
    int match(const Node *node, const std::string& x, int x_start);

    /**
     * Invokes destructor for each node in a given subtree.
     */
    void delete_all(Node *subtree);
};

#endif
