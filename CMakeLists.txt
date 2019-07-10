cmake_minimum_required(VERSION 3.14)
project(rethink)

add_subdirectory(src)
add_subdirectory(test)

add_executable(test_c src/arraylist.c)
target_link_libraries(test_c test)
message("======${CMAKE_CURRENT_SOURCE_DIR}")
# target_link_libraries(test_c algorithm)
