cmake_minimum_required(VERSION 3.14)
project(PSU_2019_malloc C)

set(CMAKE_C_STANDARD 99)

include_directories(include tests/include)
add_compile_options(-std=c99 -Wall -Wextra)



#add_library(
#        my_malloc.so
#        SHARED
#        include/my_malloc.h
#        include/internal.h
#        src/api/malloc.c
#        src/api/free.c
#        src/api/calloc.c
#        src/api/realloc.c
#        src/api/reallocarray.c
#        src/internal/arena_control.c
#        src/internal/size_control.c
#        src/internal/block_alloc.c
#        src/internal/metadata_control.c
#        src/internal/find_ptr.c
#        include/debug.h
#)

set(SRC         ${CMAKE_SOURCE_DIR}/src)
set(TESTS   ${CMAKE_SOURCE_DIR}/test)


add_test(
        tests/src/wrap_malloc.c
        -lcriterion --coverage
)


link_libraries(my_malloc.so)

add_executable(
        PSU_2019_malloc
        test_malloc.c

)