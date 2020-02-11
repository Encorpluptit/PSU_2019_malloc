#ifndef PSU_2019_MALLOC_MEMORY_H
#define PSU_2019_MALLOC_MEMORY_H

#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

// Custom free macro, to reset at NULL value.
/* #define FREE(x) free(x); x = NULL; */
/* #define free(ptr) (free(&ptr)) */

enum {
    STOCK,
    GIVE,
} memory_e;

#ifdef _DEBUG_

#include <stdio.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define dbg(x) write(1, x"\n", sizeof(x))
#define dbg_local                                   \
    (printf("[ %s ] - [ %s():%d ] ==> ",            \
            __FILENAME__,                           \
            __func__,                               \
            __LINE__))

#define dbg_pf(x, ...)                              \
    dbg_local;                                      \
    printf(x"\n", __VA_ARGS__);


#define dbg_begin(of, x, ...)                           \
    dbg_local;                                          \
    printf("[ begin: %s]\t"x"\n", of, __VA_ARGS__)

#define dbg_end(of, x, ...)                             \
    dbg_local;                                          \
    printf("[ end: %s]\t"x"\n", of, __VA_ARGS__)

#define dbg_loop(count, x, ...)                             \
    dbg_local;                                              \
    printf("[ %d ]\t"x"\n", count, __VA_ARGS__)

#define dbg_beginf(x, ...) dbg_begin("func", x, __VA_ARGS__)
#define dbg_endf(x, ...) dbg_end("func", x, __VA_ARGS__)


#else
#define dbg(x)
#define dbg_pf(x, ...)
#define dbg_begin(of, x, ...)
#define dbg_end(of, x, ...)
#define dbg_loop(of, x, ...)
#define dbg_beginf(x, ...)
#define dbg_endf(x, ...)
#endif /* _DEBUG_ */

//typedef struct metadata_s metadata_t;
typedef struct metadata_s {
    struct metadata_s *next;
    struct metadata_s *prev;
    size_t sz;
    bool free;
//    void *user_ptr;
} metadata_t;

typedef struct block_s {
    struct block_s *prev;
    struct block_s *next;
    size_t sz;
    struct metadata_s *metadata;
} block_t;

#define ELEM_PTR(x) offsetof(ptr_t, x)
#define MALLOC_INIT_SZ 40
#define PAGE_SZ (arena_get_page_size() * 2)
#define METADATA_H_SZ sizeof(metadata_t)
#define MIN_METADATA_SZ (METADATA_H_SZ * 2)
#define BLOCK_H_SZ sizeof(block_t)

#define BLOCK_OFFSET(x) (void *)((uintptr_t)x + BLOCK_H_SZ)
#define METADATA_OFFSET(x) ((void *)((uintptr_t)x + METADATA_H_SZ))
#define GET_METADATA_PTR(x) ((void *)((uintptr_t)x - METADATA_H_SZ))

#ifndef INTERNAL
#define INTERNAL
//#define INTERNAL __attribute__((visibility ("hidden")))
#endif /* HIDDEN */

// Custom free macro, to reset at NULL value.
/* #define FREE(x) free(x); x = NULL; */
/* #define free(ptr) (free(&ptr)) */


// size_control.c
INTERNAL size_t align(size_t sz);


// arena_control.c
INTERNAL block_t *arena_control();

INTERNAL int arena_get_page_size(void);


// block_alloc.c
INTERNAL bool add_in_block_list(block_t **list, block_t *ptr, size_t sz);

INTERNAL void *request_block(size_t sz);



// metadata_control.c
INTERNAL bool split_metadata(metadata_t **p_metadata);
//bool split_metadata(metadata_t **p_block, size_t offset);

INTERNAL bool merge_metadata(metadata_t *metadata, metadata_t *to_merge);
INTERNAL bool _merge_metadata(metadata_t *metadata);

metadata_t *find_ptr(void *ptr);

//bool insert_into(metadata_t *new_ptr, size_t sz);
//
//bool add_in_list(metadata_t **p_list, void *p_ptr);

// API
void *my_malloc(size_t sz);

void *my_calloc(size_t nmem, size_t sz);

void *my_realloc(void *ptr, size_t sz);
//
//void *my_reallocarray(void *ptr, size_t nmemb, size_t size);
//

void my_free(void *ptr);

//void free(void **p_to_free);

//void hello(void);

#endif //PSU_2019_MALLOC_MEMORY_H
