CC = g++
CFLAGS=  -I/usr/include/graphviz --std=gnu++11 -Wall -g
LIBS=-lgvc -lcgraph

all: trie test_tree visualize_tree create_tests test_performance

visualize_tree: visualize_tree.o tree.o node.o array_node.o hashmap_node.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test_tree: test_tree.o tree.o node.o array_node.o hashmap_node.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

visualize_tree.o: visualize_tree.cpp tree.o node.o array_node.o
	$(CC) $(CFLAGS) -c -o $@ $< 

test_tree.o: test_tree.cpp tree.o node.o array_node.o hashmap_node.o
	$(CC) $(CFLAGS) -c -o $@ $<

tree.o: tree.cpp tree.h node.o
	$(CC) $(CFLAGS) -c -o $@ $< 

node.o: node.cpp node.h
	$(CC) $(CFLAGS) -c -o $@ $< 

array_node.o: array_node.cpp array_node.h node.o
	$(CC) $(CFLAGS) -c -o $@ $< 

hashmap_node.o: hashmap_node.cpp hashmap_node.h node.o
	$(CC) $(CFLAGS) -c -o $@ $< 

trie: trie.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

trie.o: trie.cpp trie.h
	$(CC) $(CFLAGS) -c -o $@ $< 

create_tests: create_tests.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

create_tests.o: create_tests.cpp
	$(CC) $(CFLAGS) -c -o $@ $< 

test_performance: test_performance.o tree.o node.o array_node.o hashmap_node.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test_performance.o : test_performance.cpp
	$(CC) $(CFLAGS) -c -o $@ $< 

.PHONY: clean all

clean:
	rm *.o *~ trie tree test_tree visualize_tree create_tests test_performance
