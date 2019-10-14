// WEEK 2 CHALLENGE - REORDER DISJOINTED SETS

/*
Modify the implementation of DisjointSets::find(int i) below so that it performs path compression.

If the up-tree array d.s is loaded with a disjoint set such that each element points to the next element until the last element which holds a -1, then the last element is the root and its index in the array is the name of the set.

After calling find() on one of the elements in the set, the find function should (1) return the name of the disjoint set (the index of its root element) and (2) set that element in the up-tree array and all of its ancestors to point directly to the root.
/*

#include <iostream>

class DisjointSets {
public:
	int s[256];

	DisjointSets() { for (int i = 0; i < 256; i++) s[i] = -1; }

	int find(int i);
};

/* Modify the find() method below
 * to implement path compression
 * so that element i and all of
 * its ancestors in the up-tree
 * point to directly to the root
 * after find() completes.
 */

int DisjointSets::find(int i) {
  if ( s[i] < 0 ) {
    return i;
  } else {
    // return find(s[i]);
    // BL: started here
    int root = find(s[i]);
    s[i] = root;
    return root;
  }
}

int main() {
  DisjointSets d;

  d.s[1] = 3;
  d.s[3] = 5;
  d.s[5] = 7;
  d.s[7] = -1;

  std::cout << "d.find(3) = " << d.find(3) << std::endl;
  std::cout << "d.s(1) = " << d.s[1] << std::endl;
  std::cout << "d.s(3) = " << d.s[3] << std::endl;
  std::cout << "d.s(5) = " << d.s[5] << std::endl;
  std::cout << "d.s(7) = " << d.s[7] << std::endl;

  return 0;
}