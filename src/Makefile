CC = g++
CFLAGS=-I/usr/local/Cellar/graphviz/2.38.0/include/graphviz --std=gnu++11 -Wall -g
DEPS = trie.h
OBJ = trie.o
LIBS=-lgvc -lcgraph

all: trie

trie: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

.PHONY: clean all

clean:
	rm *.o *~ trie
