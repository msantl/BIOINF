#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>
#include <gvc.h>

#include "trie.h"

using namespace std;

Trie::Trie() {
  start = new Node();
  root = new Node();
  for (int i = 0; i < MXA; i++) {
    start->next[i] = root;
    start->suffix_link = NULL;
  }
  root->suffix_link = start;
  top_node = root;
}

void Trie::addTransition(int t) {
  assert(t >= 0 && t < MXA);
  Node *curr_node = top_node;
  Node* prev_leaf = NULL;
  while(curr_node->next[t] == NULL) {
    Node *leaf = new Node();
    curr_node->next[t] = leaf;
    if (prev_leaf != NULL) {
      prev_leaf->suffix_link = leaf;
    } else {
      top_node = leaf;
    }
    curr_node = curr_node->suffix_link;
    prev_leaf = leaf;
  }
  prev_leaf->suffix_link = curr_node->next[t];
}

string Trie::toDot() {
  stringstream graph;
  graph << "digraph {" << endl;
  int curr_id = 0;
  dfs(root, curr_id, graph);
  graph << "}" << endl;
  return graph.str();
}

void Trie::dfs(const Node *x, int& curr_id, ostream& out) {
  int x_id = curr_id;
  for (int i = 0; i < MXA; i++) {
    if (x->next[i] != NULL) {
      curr_id++;
      out << x_id << " -> " << curr_id << "[label=" << (char)(i + 'a') << "]" << endl;
      dfs(x->next[i], curr_id, out);
    }
  }
}

void write(const char* graph) {
  GVC_t *gvc;
  Agraph_t *g;
  FILE *outf;
  gvc = gvContext();
  outf = fopen("out.png", "w");
  g = agmemread(graph);
  gvLayout(gvc, g, "dot");
  gvRender(gvc, g, "png", outf);
  gvFreeLayout(gvc, g);
  agclose(g);
  fclose(outf);
  gvFreeContext(gvc);
}

int main() {
  Trie t;
  while (true) {
    string s;
    cin >> s;
    char c = s[0];
    t.addTransition(c - 'a');
    write(t.toDot().c_str());
  }
//  cout << t.toDot();
  return 0;
}
