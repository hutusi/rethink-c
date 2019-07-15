add_library(test test_helper.c test_arraylist.c test_list.c
    test_queue.c test_bitmap.c test_matrix.c test_bstree.c)
target_include_directories(test PRIVATE ../src)
message("======${CMAKE_CURRENT_SOURCE_DIR}")
