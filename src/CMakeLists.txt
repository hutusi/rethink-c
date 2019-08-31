add_library(algorithm compare.c dup.c text.c
                      arraylist.c queue.c list.c bitmap.c matrix.c 
                      bstree.c avltree.c rbtree.c heap.c
                      bignum.c graph.c dijkstra.c prime.c hash.c hash_table.c
                      kmp.c bm.c sunday.c trie.c ac.c huffman.c
                      vector.c distance.c)
target_compile_options(algorithm PRIVATE ${COMPILE_OPTIONS})
target_include_directories(algorithm PRIVATE ${INCLUDE_DIRECTORIES})
