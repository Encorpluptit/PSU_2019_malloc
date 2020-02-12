#ifndef PSU_2019_MALLOC_MY_MALLOC_H
#define PSU_2019_MALLOC_MY_MALLOC_H

#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

#include "debug.h" //(@TODO remove)


//<===============================================>
//<===============================================>
// API functions prototypes. (@TODO: TO CHANGE)
void *malloc(size_t sz);

void *calloc(size_t nmem, size_t sz);

void *realloc(void *ptr, size_t sz);

void *reallocarray(void *ptr, size_t nmemb, size_t sz);

void free(void *ptr);


//<===============================================>
//<===============================================>
// Struct for holding blocks and metadatas. (@TODO: CHANGE metatata -> mdata)

typedef struct metadata_s {
    struct metadata_s *next;
    struct metadata_s *prev;
    size_t sz;
    bool free;
} metadata_t;

typedef struct block_s {
    struct block_s *prev;
    struct block_s *next;
    size_t sz;
    struct metadata_s *metadata;
} block_t;

//<===============================================>
//<===============================================>
// Essentials Constants Statics. (@TODO: TO CHANGE)
#define ELEM_PTR(x) offsetof(ptr_t, x)
#define MALLOC_INIT_SZ 20
#define PAGE_SZ (arena_get_page_size() * 40)
#define METADATA_H_SZ sizeof(metadata_t)
#define MIN_METADATA_SZ (METADATA_H_SZ * 2)
#define BLOCK_H_SZ sizeof(block_t)

#define BLOCK_OFFSET(x) (void *)((uintptr_t)x + BLOCK_H_SZ)
#define METADATA_OFFSET(x) ((void *)((uintptr_t)x + METADATA_H_SZ))
#define GET_METADATA_PTR(x) ((void *)((uintptr_t)x - METADATA_H_SZ))


// Custom free macro, to reset at NULL value.
/* #define FREE(x) free(x); x = NULL; */
/* #define free(ptr) (free(&ptr)) */

#endif //PSU_2019_MALLOC_MY_MALLOC_H
