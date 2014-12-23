#ifndef TRIE_H
#define TRIE_H

#include <string>

/**
 * Creates suffix trie in quadratic time and space.
 * It is based on Algorithm 1 from Esko Ukonnen's paper:
 * On-line construction of suffix trees.
 *
 * It also provides string representation of Trie using dot language.
 */
class Trie {
  public:
    const static int MXA = 30;

    Trie();
    void addTransition(int t);
    std::string toDot();

  private:
    struct Node {
      Node *next[MXA];
      Node *suffix_link;

      Node() {
        for (int i = 0; i < MXA; i++) {
          next[i] = NULL;
        }
        suffix_link = NULL;
      }
    };
    Node *start; // svi iz starta vode u root
    Node *root;
    Node *top_node;

    void dfs(const Node *x, int& curr_id, std::ostream& out);
};

#endif
