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
    const static int MXA = 30;

    Tree();

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
    struct Node {
      Node *next[MXA];
      Node *suffix_link;
      const Tree *tree;

      /**
       * Information about edge from parent to this node.
       * text[edge_start...edge_end]
       * edge_end == -1 => signifies the end of the current text
       */
      int edge_start, edge_end;

      Node(const Tree *tree, int edge_start, int edge_end) {
        for (int i = 0; i < MXA; i++) {
          next[i] = NULL;
        }
        suffix_link = NULL;
        this->edge_start = edge_start;
        this->edge_end = edge_end;
        this->tree = tree;
      }

      int edge_length() const {
        if (edge_end == INF) return tree->text.size() - edge_start;
        return edge_end - edge_start + 1;
      }
    };
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
};

