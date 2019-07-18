add_library(test alloc-testing.c test_helper.c test_arraylist.c test_list.c
    test_queue.c test_bitmap.c test_matrix.c test_bstree.c test_bignum.c)
target_compile_options(test PRIVATE -g -DALLOC_TESTING)
target_include_directories(test PRIVATE ../src)
message("======${CMAKE_CURRENT_SOURCE_DIR}")
