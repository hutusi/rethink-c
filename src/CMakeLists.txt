add_library(algorithm arraylist.c queue.c list.c bitmap.c matrix.c bstree.c)
target_compile_options(algorithm PRIVATE -g -DALLOC_TESTING)
target_include_directories(algorithm PRIVATE ../test)
