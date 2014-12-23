CC = g++
CFLAGS=-I/usr/local/Cellar/graphviz/2.38.0/include/graphviz --std=gnu++11 -Wall -g
LIBS=-lgvc -lcgraph

all: trie test_tree visualize_tree

trie: trie.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

visualize_tree: visualize_tree.o tree.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test_tree: test_tree.o tree.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

visualize_tree.o: visualize_tree.cpp tree.o
	$(CC) $(CFLAGS) -c -o $@ $< 

test_tree.o: test_tree.cpp tree.o
	$(CC) $(CFLAGS) -c -o $@ $<

tree.o: tree.cpp tree.h
	$(CC) $(CFLAGS) -c -o $@ $< 

trie.o: trie.cpp trie.h
	$(CC) $(CFLAGS) -c -o $@ $< 


.PHONY: clean all

clean:
	rm *.o *~ trie tree test_tree visualize_tree
