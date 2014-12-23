#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>

/**
 * Creates suffix tree in linear time and space.
 * It is based on Algorithm from Esko Ukonnen's paper:
 * On-line construction of suffix trees.
 *
 * It also provides string representation of Tree using dot language.
 * Maximum alphabet size is 30.
 */
class Tree {
  public:
    Tree(int alphabet_size);

    ~Tree();

    void addTransition(int t);

    /**
     * Returns true if string x is in this tree.
     * Elements in string are interpreted as integers by subtracting 'a' from
     * them.
     */
    bool find(const std::string& x);

    std::string toDot();

  private:
    const static int INF = -2;
    class Node {
      public:
        Node *suffix_link;
        const Tree *tree;

        /**
         * Information about edge from parent to this node.
         * text[edge_start...edge_end]
         * edge_end == -1 => signifies the end of the current text
         */
        int edge_start, edge_end;

        Node(const Tree *tree, int edge_start, int edge_end) {
          this->next = new Node*[tree->alphabet_size];
          for (int i = 0; i < tree->alphabet_size; i++) {
            next[i] = NULL;
          }
          suffix_link = NULL;
          this->edge_start = edge_start;
          this->edge_end = edge_end;
          this->tree = tree;
          this->cnt = 0;
        }

        ~Node() {
          delete[] next;
        }
/*
        Node *& operator[] (int i) {
          return next[i];
        }
*/
        void set(int t, Node* node) {
          next[t] = node;
        }

        void unset(int t, Node* node) {
          next[t] = NULL;
        }

        Node * operator[] (int i) const {
          return next[i];
        }

        size_t size() const {
          return cnt;
        }

        int edge_length() const {
          if (edge_end == INF) return tree->text.size() - edge_start;
          return edge_end - edge_start + 1;
        }

        class iterator {
          public:
            iterator(Node **pos, Node **end_pos) : pos_(pos), end_pos_(end_pos) {
             advance();
            }

            bool operator==(const iterator& rhs) const {
              return pos_ == rhs.pos_;
            }

            bool operator!=(const iterator& rhs) const {
              return pos_ != rhs.pos_;
            }

            iterator& operator++() {
              pos_++;
              advance();
              return *this;
            }

            Node*& operator*() const {
              return *pos_;
            }

            Node* operator->() const {
              return *pos_;
            }

          private:
            Node **pos_;
            Node **end_pos_;

            void advance() {
              for (; *pos_ == NULL && pos_ != end_pos_; pos_++);
            }
        };

        iterator begin() {
          return iterator(next, next + tree->alphabet_size);
        }

        iterator end() {
          return iterator(next + tree->alphabet_size, next +
              tree->alphabet_size);
        }

      private:
        size_t cnt;
        Node **next;
    };

    int alphabet_size;
    Node *start; // svi iz starta vode u root
    Node *root;

    Node *active_node;
    int active_start, active_end;
    std::vector <int> text;

    Node* split(Node *x, int l, int r, int t);
    std::pair <Node*, int> canonize(Node *x, int l, int r);
    void dfs(const Node *x, int& curr_id, std::ostream& out);
    std::string transition(const Node *x, int t);
    int match(const Node *node, const std::string& x, int x_start);
    void delete_all(Node *subtree);
};

#endif
