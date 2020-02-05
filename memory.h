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


#define dbg(x) write(1, x"\n", sizeof(x))

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

ptr_t **get_arena_alloc();

ctrl_t *arena_control();

bool insert_into(ptr_t *new_ptr, size_t size);

bool add_in_list(ptr_t **p_list, void *p_ptr);

void *malloc(size_t size);
//
//void *calloc(size_t nmemb, size_t size);
//
//void *realloc(void *ptr, size_t size);
//
//void *reallocarray(void *ptr, size_t nmemb, size_t size);
//
void my_free(void **p_to_free);

//void hello(void);

#endif //PSU_2019_MALLOC_MEMORY_H
