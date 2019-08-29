add_executable(deflate deflate.c)
target_link_libraries(deflate algorithm testcases)
target_compile_options(deflate PRIVATE ${COMPILE_OPTIONS})
target_include_directories(deflate PRIVATE ${INCLUDE_DIRECTORIES})

add_executable(inflate inflate.c)
target_link_libraries(inflate algorithm testcases)
target_compile_options(inflate PRIVATE ${COMPILE_OPTIONS})
target_include_directories(inflate PRIVATE ${INCLUDE_DIRECTORIES})
