#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "tree.h"

using namespace std;

Tree::Tree(int alphabet_size) {
  this->alphabet_size = alphabet_size;
  start = new Node(this, -1, -1);
  root = new Node(this, -1, -1);
  for (int i = 0; i < alphabet_size; i++) {
    start->set(i, root);
    // (*start)[i] = root;
    start->suffix_link = NULL;
  }
  root->suffix_link = start;
  active_node = root;
  active_start = 0;
  active_end = -1;
  text = vector<int>();
}

Tree::~Tree() {
  delete_all(root);
  delete start;
}

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
Tree::Node* Tree::split(Node *x, int l, int r, int t) {
  int len = r - l + 1;
  if (r == INF) len = text.size() - l;
  if (l <= r || r == INF) {
    assert(l < text.size());
    int next_t = text[l];
    Node *next = (*x)[next_t];
    assert(next != NULL);
    assert(next->edge_start + len < text.size());
    if (t == text[next->edge_start + len]) {
      return NULL; // end point
    } else {
      Node *ret = new Node(this, next->edge_start, next->edge_start + len - 1);
      ret->set(text[next->edge_start + len], next);
      next->edge_start += len;
      x->set(next_t, ret);
      // (*x)[next_t] = ret;
      return ret;
    }
  }
  // l > r ==> empty string
  Node *next = (*x)[t];
  if (next != NULL) return NULL;
  return x;
}

/**
 * Returns canonized state which is corresponds to the one givven in params.
 * r is not returned because it never changes.
 */
pair <Tree::Node*, int> Tree::canonize(Node *x, int l, int r) {
  while(true) {
    if (r < l) break;
    Node *next = (*x)[text[l]];
    if (next == NULL || next->edge_length() > r - l + 1) break;
    l += next->edge_length();
    x = next;
  }
  return make_pair(x, l);
}

void Tree::addTransition(int t) {
  assert(t >= 0 && t < alphabet_size);
  active_end++;
  text.push_back(t);
  Node *prev_node = root;
  while(true) {
    Node *split_node = split(active_node, active_start, active_end - 1, t);
    if (split_node == NULL) break;
    split_node->set(t, new Node(this, active_end, INF));
    if (prev_node != root) { // if not first iteration
      prev_node->suffix_link = split_node;
    }
    prev_node = split_node;
    pair <Tree::Node*, int> canonized =
      canonize(active_node->suffix_link, active_start, active_end - 1);
    active_node = canonized.first;
    active_start = canonized.second;
  }
  if (prev_node != root) {
    prev_node->suffix_link = active_node;
  }
  pair <Tree::Node*, int> canonized =
      canonize(active_node, active_start, active_end); // Lemma 2
  active_node = canonized.first;
  active_start = canonized.second;
}

string Tree::toDot() {
  stringstream graph;
  graph << "digraph {" << endl;
  int curr_id = 0;
  dfs(root, curr_id, graph);
  graph << "}" << endl;
  return graph.str();
}

string Tree::transition(const Node *x, int t) {
  const Node *next = (*x)[t];
  if (next == NULL) return "";
  int l = next->edge_start;
  int r = next->edge_end;
  if (r == INF) r = text.size() - 1;
  if (l < 0) l = 0;
  string ret = "";
  for (; l <= r; l++) {
    ret += text[l] + 'a';
  }
  return ret;
}

void Tree::dfs(const Node *x, int& curr_id, ostream& out) {
  int x_id = curr_id;
  for (int i = 0; i < alphabet_size; i++) {
    if ((*x)[i] != NULL) {
      curr_id++;
      out << x_id << " -> " << curr_id
        << "[label=" << transition(x, i) << "]"
        << endl;
      dfs((*x)[i], curr_id, out);
    }
  }
}

int Tree::match(const Node *node, const string& x, int x_start) {
  int mn_len = min(node->edge_length(), (int)x.size() - x_start);
  for (int i = 0; i < mn_len; i++) {
    if (text[node->edge_start + i] + 'a' != x[i + x_start]) return -1;
  }
  return mn_len;
}

bool Tree::find(const string& x) {
  const Node* curr = root;
  for (int x_i = 0; x_i < x.size();) {
    const Node* next = (*curr)[x[x_i] - 'a'];
    if (next == NULL) return false;
    int mn_len = match(next, x, x_i);
    if (mn_len == -1) return false;
    x_i += mn_len;
    curr = next;
  }
  return true;
}

void Tree::delete_all(Node *subtree) {
  if (subtree == NULL) return;
  for (Node::iterator it = subtree->begin(); it != subtree->end(); ++it) {
    delete_all(*it);
  }
  delete subtree;
}
