#include <iostream>
#include <gvc.h>

#include "tree.h"

using namespace std;

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

/**
 *  Reads string, char by char.
 *  Creates out.png with the visualization of tree as each char is read.
 */
int main() {
  Tree t;
  while (true) {
    string s;
    cin >> s;
    char c = s[0];
    t.addTransition(c - 'a');
    write(t.toDot().c_str());
  }
  return 0;
}
