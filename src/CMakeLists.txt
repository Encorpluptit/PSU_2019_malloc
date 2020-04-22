cmake_minimum_required(VERSION 3.14)
project(PSU_2019_malloc C)

set(CMAKE_C_STANDARD 99)

add_library(
        my_malloc
        SHARED
        api/malloc.c
        api/free.c
        api/calloc.c
        api/realloc.c
        api/reallocarray.c
        internal/arena_control.c
        internal/size_control.c
        internal/block_alloc.c
        internal/metadata_control.c
        internal/find_ptr.c
)
