//
// Created by dbernard on 2/8/20.
//

#include "memory.h"

void *request_block(size_t sz) {
    void *heap = sbrk(align(sz - 1));

    if (heap == (void *) -1)
        return NULL;
    dbg_pf("REQUEST BLOCK: %zd, \t%p", align(sz - 1), heap);
    return heap;
}

static block_t *init_block(block_t *ptr, size_t sz, block_t *prev, block_t *next) {
    *ptr = (block_t) {
            .sz = sz,
            .next = next, .prev = prev,
            .metadata = BLOCK_OFFSET(ptr)};
    (*ptr->metadata) = (metadata_t) {
            .sz = sz - BLOCK_H_SZ - METADATA_H_SZ,
            .next = NULL, .prev = NULL,
            .user_ptr = METADATA_OFFSET(BLOCK_OFFSET(ptr))};
    if (next)
        next->prev = ptr;
    return ptr;
};

bool add_in_block_list(block_t **p_list, block_t *ptr, size_t sz) {
    block_t *list = *p_list;

    if (!list) {
        *p_list = init_block(ptr, sz, *p_list, NULL);
        dbg_pf("[ADD BLOCK - ARENA INIT] %p,\tSize: %zd",
                *p_list, (*p_list)->sz);
        dbg_pf("[ADD BLOCK - ARENA INIT] METADATA - Ptr: %p,\tSize: %zd",
                (*p_list)->metadata, (*p_list)->metadata->sz);
        return true;
    }
    for (; list->next && list->next != *p_list; list = list->next);
//    for (; list->next && list->next != *p_list; list = list->next) {
    //        dbg_pf("[ ADD BLOCK LOOP ]: %p", list);
//    }
    dbg_pf("[ ADD BLOCK LOOP ==> END ]: %p", list);
    list->next = init_block(ptr, sz, list, *p_list);
    dbg_pf("[ADD BLOCK - ARENA INIT] METADATA - Ptr: %p,\tSize: %zd",
            list->metadata, list->metadata->sz);
    return true;
}
