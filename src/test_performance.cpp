#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <sys/types.h>
#include <unistd.h>

#include "tree.h"
#include "hashmap_node.h"
#include "array_node.h"

using namespace std;

const int NUM_ALPHABET = 30;

Node* create_hash_node(const Tree *tree, int edge_start, int edge_end) {
  return new HashmapNode(tree, edge_start, edge_end);
}

Node* create_array_node(const Tree *tree, int edge_start, int edge_end) {
  return new ArrayNode(tree, edge_start, edge_end);
}

int file_char_cnt(const char *filename) {
  int ret = 0;
  FILE* f = fopen(filename, "r");

  while (fgetc(f) != EOF) {
    ret += 1;
  }

  fclose(f);
  return ret;
}

Tree* create_tree(const char *filename, 
    Node* (*create_node)(const Tree*, int, int),
    char offset) {

  Tree* t = new Tree(NUM_ALPHABET, create_node);
  char buffer[512];
  FILE* test;

  test = fopen(filename, "r");

  while (fgets(buffer, sizeof buffer, test)) {
    int n = strlen(buffer);
    for (int i = 0; i < n; ++i) {
      t->add_transition(buffer[i] - offset);
    }
  }

  fclose(test);

  return t;
}

int get_memory_usage(void) {
  FILE *f;
  size_t len;
  int pid = getpid(), ret;
  char filename[256];
  memset(filename, 0, sizeof filename);
  sprintf(filename, "/proc/%d/status", pid);

  char *line;
  char *vmsize;

  vmsize = NULL;
  len = 128;
  line = (char *)malloc(len);
  
  f = fopen(filename, "r");

  if (!f) return -1;
  
  while (!vmsize) {
    if (getline(&line, &len, f) == -1) {
      return 1;
    }
    
    if (!strncmp(line, "VmSize:", 7)) {
      vmsize = strdup(&line[7]);
    }
    
  }

  free(line);
  fclose(f);

  len = strlen(vmsize);
  vmsize[len - 4] = 0;
  
  sscanf(vmsize, "%d", &ret);
  
  free(vmsize);
  usleep(100000);

  return ret;
}

int main() {
  const int TEST_CNT = 225;
  char filename[256];

  printf("Izgradnja sufiksnog stabla (2 verzije cvora) %d\n", getpid());
  printf("%10s\t%10s\t%10s\t%10s\t%10s\n", 
      "char cnt", 
      "hashmap t", 
      "hashmap m", 
      "array t", 
      "array m");

  for (int i = 0; i < TEST_CNT; ++i) {
    memset(filename, 0, sizeof filename);
    sprintf(filename, "../tests/test.%d.in", i);
    int m1, m2;

    clock_t t1 = clock();
    /* hashmap node */
    {
      Tree* t = create_tree(filename, create_hash_node, 'A');
      m1 = get_memory_usage();
      delete t;
    }
    clock_t t2 = clock();
    usleep(100000);

    /* array node */
    clock_t t3 = clock();
    {
      Tree* t = create_tree(filename, create_array_node, 'A');
      m2 = get_memory_usage();
      delete t;
    }
    clock_t t4 = clock();
    usleep(100000);

    printf("%10d\t%10.3lf\t%10d\t%10.3lf\t%10d\n",
        file_char_cnt(filename),
        (double)(t2 - t1) / CLOCKS_PER_SEC, 
        m1,
        (double)(t4 - t3) / CLOCKS_PER_SEC,
        m2);
  }
  return 0;
}
