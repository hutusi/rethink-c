# RETHINK C

Relearn and rethink C Programming Language, including some of data structures and algorithms.

The code is licensed under the MIT license, copyright by [hutusi.com](http://hutusi.com/).

Some of the code inspired (copied) by Simon Howard's [c-algorithms](https://github.com/fragglet/c-algorithms), like ArrayList, etc. This project also reused his alloc-testing framework for memory testing.

RETHINK-C aims to build a reuseable codebase for C Programming Language. 

## How to build & test

### Requirements:

* Editor/IDE: VS Code is recommended.
* GCC on Mac, Linux or Windows. (Recommend msys2 + MingW on Windows.)
* CMake. 
* Clang-Format.

### build & test:

* build 

```
cd build
cmake ..
make
```

* test:

```
make test
```

## Goals / Achievements

### Basic Data Structures

- [x] ArrayList, Stack [arraylist.h](src/arraylist.h) [arraylist.c](src/arraylist.c)
- [x] LinkedList [list.h](src/list.h) [list.c](src/list.c)
- [x] Queue [queue.h](src/queue.h) [queue.c](src/queue.c)
- [x] BitMap [bitmap.h](src/bitmap.h) [bitmap.c](src/bitmap.c)
- [x] Muti-dimensional Matrix [matrix.h](src/matrix.h) [matrix.c](src/matrix.c)
- [x] Hash Table [hash_table.h](src/hash_table.h) [hash_table.c](src/hash_table.c) [hash.h](src/hash.h) [hash.c](src/hash.c)

### Trees
- [x] Binary Search Tree [bstree.h](src/bstree.h) [bstree.c](src/bstree.c)
- [x] AVL Tree [avltree.h](src/avltree.h) [avltree.c](src/avltree.c)
- [x] Red Black Tree [rbtree.h](src/rbtree.h) [rbtree.c](src/rbtree.c)
- [x] Binary Heap [heap.h](src/heap.h) [heap.c](src/heap.c)
- [ ] B+ Tree

### Graphs
- [x] Adjacency Matrix [graph.h](src/graph.h) [graph.c](src/graph.c)
- [ ] Union-Find
- [ ] BFS & DFS
- [ ] Topological sorting
- [ ] Floyd
- [x] Dijkstra [dijkstra.h](src/dijkstra.h) [dijkstra.c](src/dijkstra.c)
- [ ] Prim
- [ ] Kruskal

### String, Text.
- [x] Text (similar to string in C++). [text.h](src/text.h) [text.c](src/text.c)
- [x] BigNum integer [bignum.h](src/bignum.h) [bignum.c](src/bignum.c)
- [ ] BigNum decimal
- [x] KMP (Knuth-Morris-Pratt) algorithm [kmp.h](src/kmp.h) [kmp.c](src/kmp.c)
- [x] BM (Boyer-Moore) algorithm [bm.h](src/bm.h) [bm.c](src/bm.c)
- [x] Sunday algorithm [sunday.h](src/sunday.h) [sunday.c](src/sunday.c)
- [x] Trie Tree [trie.h](src/trie.h) [trie.c](src/trie.c)
- [x] Aho–Corasick algorithm [ac.h](src/ac.h) [ac.c](src/ac.c)
- [ ] DAT (Double-Array Trie)
- [ ] Huffman coding

### Sorting
- [x] Quick Sort [arraylist.c##arraylist_sort()](src/arraylist.c)
- [x] Merge Sort [list.c##list_sort()](src/list.c)

### Math
- [ ] Matrix multiplication
- [x] Eratosthenes sieve (prime numbers) [prime.h](src/prime.h) [prime.c](src/prime.c)
- [ ] Carmichael Numbers (prime number)
