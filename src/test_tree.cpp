#include <iostream>
#include <algorithm>
#include <cassert>

#include "tree.h"

using namespace std;

const int NUM_ALPHABET = 30;

void find_all_subs(Tree *t, const string& x) {
  for (int l = 0; l < (int)x.size(); l++) {
    for (int r = l; r < (int)x.size(); r++) {
      string s = x.substr(l, r - l + 1);
      assert(t->find(s));
    }
  }
}

void testAllSubs() {
  string x;
  for (int i = 0; i < 300; i++)
    x += (rand() % 7 + 'a');
  Tree t(NUM_ALPHABET);
  for (char c : x) {
    t.add_transition(c - 'a');
  }
  find_all_subs(&t, x);
  cout << "testAllSubs done." << endl;
}

void testRandom() {
  int n = 1000;
  const int MXA = 5;
  string s;
  Tree t(NUM_ALPHABET);
  for (int i = 0; i < n; i++) {
    char c = 'a' + rand() % MXA;
    s += c;
    t.add_transition(c - 'a');
  }
  find_all_subs(&t, s);
  for (int i = 0; i < 100; i++) {
    int l = rand() % n;
    int len = rand() % (n - l) + 1;
    string x = s.substr(l, len);
    x[rand() % len] = 'a';
    bool found1 = s.find(x) != string::npos;
    bool found2 = t.find(x);
    assert(found1 == found2);
  }
  cout << "testRandom done" << endl;
}

void testRandomBig() {
  int n = 1000000;
  const int MXA = 5;
  string s;
  Tree t(NUM_ALPHABET);
  for (int i = 0; i < n; i++) {
    char c = 'a' + rand() % MXA;
    s += c;
    t.add_transition(c - 'a');
  }
  cout << "Tree is created" << endl;
  for (int i = 0; i < 100; i++) {
    int l = rand() % n;
    int len = min(1000, rand() % (n - l) + 1);
    string x = s.substr(l, len);
    x[rand() % len] = 'a';
    bool found1 = s.find(x) != string::npos;
    bool found2 = t.find(x);
    assert(found1 == found2);
  }
  cout << "testRandomBig done" << endl;
}

int main() {
  testRandom();
  testRandomBig();
  testAllSubs();
  return 0;
}
