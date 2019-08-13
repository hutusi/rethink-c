cmake_minimum_required(VERSION 3.14)
project(rethink)

# set(COMPILE_OPTIONS -std=c99 -O2 -Wall -g -DALLOC_TESTING)
set(COMPILE_OPTIONS -std=c99 -Wall -g -DTESTING -DALLOC_TESTING)
set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/src 
                        ${CMAKE_CURRENT_SOURCE_DIR}/test)

# message("======${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(src)
add_subdirectory(test)

# CTest
enable_testing()

add_executable(unit_tests test/testmain.c)
target_link_libraries(unit_tests testcases algorithm)
target_compile_options(unit_tests PRIVATE ${COMPILE_OPTIONS})

add_test(test_all unit_tests)
