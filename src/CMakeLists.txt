add_library(algorithm arraylist.c queue.c list.c bitmap.c matrix.c bstree.c bignum.c)
target_compile_options(algorithm PRIVATE ${COMPILE_OPTIONS})
target_include_directories(algorithm PRIVATE ${INCLUDE_DIRECTORIES})
