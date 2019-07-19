cmake_minimum_required(VERSION 3.14)
project(rethink)

set(COMPILE_OPTIONS -Wall -g -DALLOC_TESTING)
set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/src 
                        ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_executable(testmain test/testmain.c)
target_link_libraries(testmain algorithm test)
target_compile_options(testmain PRIVATE ${COMPILE_OPTIONS})
# message("======${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(src)
add_subdirectory(test)
