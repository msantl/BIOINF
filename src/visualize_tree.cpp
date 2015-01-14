#include <iostream>
#include <string>
#include <sstream>
#include <gvc.h>

#include "tree.h"
#include "hashmap_node.h"

using namespace std;

void write(const char* graph, const char* filename) {
  GVC_t *gvc;
  Agraph_t *g;
  FILE *outf;
  gvc = gvContext();
  outf = fopen(filename, "w");
  g = agmemread(graph);
  gvLayout(gvc, g, "dot");
  gvRender(gvc, g, "png", outf);
  gvFreeLayout(gvc, g);
  agclose(g);
  fclose(outf);
  gvFreeContext(gvc);
}

Node* create_node(const Tree *tree, int edge_start, int edge_end) {
  return new HashmapNode(tree, edge_start, edge_end);
}

/**
 *  Reads string, char by char.
 *  Creates out.png with the visualization of tree as each char is read.
 */
int main() {
  const int NUM_ALPHABET = 30;
  Tree t(NUM_ALPHABET, create_node);
  int id = 1;
  while (true) {
    string s;
    cin >> s;
    char c = s[0];
    t.add_transition(c - 'a');
    stringstream filename;
    filename << "out_" << id << ".png";
    write(t.toDot().c_str(), filename.str().c_str());
    id++;
  }
  return 0;
}
