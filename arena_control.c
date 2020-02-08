//
// Created by dbernard on 2/8/20.
//

#include <stdlib.h>
#include "memory.h"


void *request_block(size_t sz) {
    void *heap = sbrk(align(sz - 1));

    if (heap == (void *) -1)
        return NULL;
    dbg_pf("REQUEST BLOCK: %zd, \t%p", align(sz - 1), heap);
    return heap;
}

bool add_in_block_list(block_t **p_list, block_t *ptr, size_t sz) {
    block_t *list = *p_list;

    if (!list) {
        *p_list = ptr;
        *ptr = (block_t) {.sz = sz, .next = NULL, .metadata = BLOCK_OFFSET(ptr)};
        dbg_pf("[ADD BLOCK - ARENA INIT] %p,\tSize: %zd", *p_list, (*p_list)->sz);
        (*ptr->metadata) = (mdata_t) {.sz = sz - BLOCK_H_SZ - METADATA_H_SZ,
                .next = NULL, .user_ptr = METADATA_OFFSET(BLOCK_OFFSET(ptr))};
        dbg_pf("[ADD BLOCK - ARENA INIT] METADATA - Ptr: %p,\tSize: %zd", (*p_list)->metadata, (*p_list)->metadata->sz);
        return true;
    }
    for (; list->next; list = list->next);
//    for (; list->next; list = list->next) {
//        dbg_pf("[ ADD BLOCK LOOP ]: %p", list);
//    }
    dbg_pf("[ ADD BLOCK LOOP ==> END ]: %p", list);
    list->next = ptr;
    *ptr = (block_t) {.sz = sz, .next = NULL, .metadata = BLOCK_OFFSET(ptr)};
    (*ptr->metadata) = (mdata_t) {.sz = sz - BLOCK_H_SZ - METADATA_H_SZ,
            .next = NULL, .user_ptr = METADATA_OFFSET(BLOCK_OFFSET(ptr))};
    dbg_pf("[ADD BLOCK - ARENA INIT] METADATA - Ptr: %p,\tSize: %zd", list->metadata, list->metadata->sz);
    return true;
}

static void *init_arena(block_t *arena) {
    block_t *heap = NULL;

    for (uint8_t i = 1; i <= MALLOC_INIT_SZ; ++i) {
        if (!(heap = request_block(PAGE_SZ)))
            return NULL;
        add_in_block_list(&arena, heap, PAGE_SZ);
    }
    return arena;
}

block_t *arena_control() {
    static block_t *arena = NULL;

    if (!arena) {
        dbg_pf("ARENA NULL: %p", arena);
        if (!(arena = init_arena(arena)))
            exit(84);
        dbg_pf("END INIT ARENA: %p,\t%p", arena, BLOCK_OFFSET(arena));
    }
    dbg_pf("GIVE ARENA: %p", arena);
    return arena;
}
