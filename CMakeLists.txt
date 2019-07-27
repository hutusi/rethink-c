cmake_minimum_required(VERSION 3.14)
project(rethink)

set(COMPILE_OPTIONS -std=c99 -O2 -Wall -g -DALLOC_TESTING)
set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/src 
                        ${CMAKE_CURRENT_SOURCE_DIR}/test)

# message("======${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(src)
add_subdirectory(test)

add_executable(testmain test/testmain.c)
target_link_libraries(testmain test algorithm)
target_compile_options(testmain PRIVATE ${COMPILE_OPTIONS})