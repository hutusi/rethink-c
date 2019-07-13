add_library(test test_list.c test_helper.c)
target_include_directories(test PRIVATE ../src)
message("======${CMAKE_CURRENT_SOURCE_DIR}")
