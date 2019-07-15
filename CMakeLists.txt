cmake_minimum_required(VERSION 3.14)
project(rethink)

add_subdirectory(src)
add_subdirectory(test)

add_executable(testmain test/testmain.c)
target_link_libraries(testmain algorithm test)
target_compile_options(testmain PRIVATE -g -DALLOC_TESTING)
# message("======${CMAKE_CURRENT_SOURCE_DIR}")
