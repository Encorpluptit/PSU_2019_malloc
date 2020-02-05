#ifndef PSU_2019_MALLOC_MEMORY_H
#define PSU_2019_MALLOC_MEMORY_H

#include <stdbool.h>
#include <unistd.h>
//#include <stddef.h>
#include <stdint.h>
#include <zconf.h>

// Custom free macro, to reset at NULL value.
/* #define FREE(x) free(x); x = NULL; */
/* #define free(ptr) (my_free(&ptr)) */

enum {
    STOCK,
    GIVE,
} EMemory;

#ifdef _DEBUG_
#include <stdio.h>

#define dbg(x) write(1, x"\n", sizeof(x))
#define dbg_local                               \
    (printf("[ %s ] - [ %s():%d ]",             \
            __FILE__,                           \
            __func__,                           \
            __LINE__))
/*
#define dbg(x, ...)                             \
    dbg_local;                                  \
    printf(x"\n", __VA_ARGS__)
*/

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
#define dbg(x, ...)
#define dbg_begin(of, x, ...)
#define dbg_end(of, x, ...)
#define dbg_loop(of, x, ...)
#define dbg_beginf(x, ...)
#define dbg_endf(x, ...)
#endif /* _DEBUG_ */

typedef struct ptr_s ptr_t;
struct ptr_s {
    ptr_t *next;
    ptr_t *prev;
    void *user_ptr;
    size_t size;
    bool free;
//    void *data;
//    char data[1];
};

typedef struct control_struct_s {
    ptr_t *alloc;
    ptr_t *free;
} ctrl_t;

#define HEADER_SZ offsetof(ptr_t, block)
#define PAGE_SZ (getpagesize() * 2)
#define MALLOC_INIT_SZ 10

// Custom free macro, to reset at NULL value.
/* #define FREE(x) free(x); x = NULL; */
/* #define free(ptr) (my_free(&ptr)) */

ptr_t **get_arena_alloc();

ptr_t **get_arena_free();

ctrl_t *arena_control();

bool insert_into(ptr_t *new_ptr, size_t size);

bool add_in_list(ptr_t **p_list, void *p_ptr);

void *my_malloc(size_t size);

//
//void *calloc(size_t nmemb, size_t size);
//
//void *realloc(void *ptr, size_t size);
//
//void *reallocarray(void *ptr, size_t nmemb, size_t size);
//
//void my_free(void **p_to_free);

//void hello(void);

#endif //PSU_2019_MALLOC_MEMORY_H
