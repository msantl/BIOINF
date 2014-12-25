#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "tree.h"
#include "node.h"

using namespace std;

Node* Tree::create_node(const Tree *tree, int edge_start, int edge_end) {
  return create_ptr_(tree, edge_start, edge_end);
}

Tree::Tree(int alphabet_size, Node* (*create_ptr)(const Tree*, int, int)) {
  this->alphabet_size = alphabet_size;
  this->create_ptr_ = create_ptr;
  start = create_node(this, -1, -1);
  root = create_node(this, -1, -1);
  for (int i = 0; i < alphabet_size; i++) {
    start->set(i, root);
    start->suffix_link_ = NULL;
  }
  root->suffix_link_ = start;
  active_node = root;
  active_start = 0;
  active_end = -1;
  text = vector<int>();
}

Tree::~Tree() {
  root->delete_subtree();
  delete start;
  delete root;
}


Node* Tree::split(Node *x, int l, int r, int t) {
  int len = r - l + 1;
  if (r == INF) len = text.size() - l;
  if (l <= r || r == INF) {
    assert(l < text.size());
    int next_t = text[l];
    Node *next = (*x)[next_t];
    assert(next != NULL);
    assert(next->edge_start_ + len < text.size());
    if (t == text[next->edge_start_ + len]) {
      return NULL; // end point
    } else {
      Node *ret = create_node(this, next->edge_start_, next->edge_start_ + len - 1);
      ret->set(text[next->edge_start_ + len], next);
      next->edge_start_ += len;
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


pair <Node*, int> Tree::canonize(Node *x, int l, int r) {
  while(true) {
    if (r < l) break;
    Node *next = (*x)[text[l]];
    if (next == NULL || next->edge_length() > r - l + 1) break;
    l += next->edge_length();
    x = next;
  }
  return make_pair(x, l);
}

void Tree::add_transition(int t) {
  assert(t >= 0 && t < alphabet_size);
  active_end++;
  text.push_back(t);
  Node *prev_node = root;
  while(true) {
    Node *split_node = split(active_node, active_start, active_end - 1, t);
    if (split_node == NULL) break;
    split_node->set(t, create_node(this, active_end, INF));
    if (prev_node != root) { // if not first iteration
      prev_node->suffix_link_ = split_node;
    }
    prev_node = split_node;
    pair <Node*, int> canonized =
      canonize(active_node->suffix_link_, active_start, active_end - 1);
    active_node = canonized.first;
    active_start = canonized.second;
  }
  if (prev_node != root) {
    prev_node->suffix_link_ = active_node;
  }
  pair <Node*, int> canonized =
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

string Tree::transition(const Node *x, int t) {
  const Node *next = (*x)[t];
  if (next == NULL) return "";
  int l = next->edge_start_;
  int r = next->edge_end_;
  if (r == INF) r = text.size() - 1;
  if (l < 0) l = 0;
  string ret = "";
  for (; l <= r; l++) {
    ret += text[l] + 'a';
  }
  return ret;
}

int Tree::match(const Node *node, const string& x, int x_start) {
  int mn_len = min(node->edge_length(), (int)x.size() - x_start);
  for (int i = 0; i < mn_len; i++) {
    if (text[node->edge_start_ + i] + 'a' != x[i + x_start]) return -1;
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

