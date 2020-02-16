/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** Header file for internal functions.
*/

#ifndef PSU_2019_MALLOC_INTERNAL_H
#define PSU_2019_MALLOC_INTERNAL_H

#ifndef INTERNAL
#define INTERNAL
//#define INTERNAL __attribute__((visibility ("hidden")))
//(@TODO: fix compile errror)
#endif /* HIDDEN */

//<===============================================>
//<===============================================>

typedef struct mdata_s {
    struct mdata_s *next;
    struct mdata_s *prev;
    size_t sz;
    bool free;
} mdata_t;

typedef struct block_s {
    struct block_s *prev;
    struct block_s *next;
    size_t sz;
    struct mdata_s *mdata;
} block_t;

//<===============================================>
//<===============================================>
#define ELEM_PTR(x) offsetof(ptr_t, x)
#define MALLOC_INIT_SZ 20
#define PAGE_SZ (arena_get_page_size() * 2)
#define METADATA_H_SZ sizeof(mdata_t)
#define BLOCK_H_SZ sizeof(block_t)
#define MIN_METADATA_SZ (METADATA_H_SZ + BLOCK_H_SZ)

#define BLOCK_OFFSET(x) (void *)((uintptr_t)x + BLOCK_H_SZ)
#define METADATA_OFFSET(x) ((void *)((uintptr_t)x + METADATA_H_SZ))
#define GET_METADATA_PTR(x) ((void *)((uintptr_t)x - METADATA_H_SZ))


// size_control.c
INTERNAL size_t align(size_t sz);


// arena_control.c
INTERNAL block_t *arena_control(void);

INTERNAL int arena_get_page_size(void);


// block_alloc.c
INTERNAL bool add_in_block_list(block_t **list, block_t *ptr, size_t sz);

INTERNAL void *request_block(size_t sz);



// metadata_control.c
INTERNAL bool split_mdata(mdata_t **p_mdata);

INTERNAL bool merge_mdata(mdata_t *mdata);

// find_ptr.c
INTERNAL mdata_t *find_ptr(void *ptr);

#endif //PSU_2019_MALLOC_INTERNAL_H
