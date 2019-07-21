add_library(test alloc-testing.c test_helper.c test_arraylist.c test_list.c
                 test_queue.c test_bitmap.c test_matrix.c test_bstree.c 
                 test_bignum.c test_dijkstra.c)
target_compile_options(test PRIVATE ${COMPILE_OPTIONS})
target_include_directories(test PRIVATE ${INCLUDE_DIRECTORIES})
