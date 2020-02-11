//
// Created by dbernard on 2/8/20.
//

#include <string.h>
#include "memory.h"

INTERNAL void *request_block(size_t sz) {
//    size_t new_size = align(sz - 1);
    size_t new_size = sz;
    void *heap = sbrk(new_size);

    dbg_pf("REQUEST BLOCK: %zd, \t%p", new_size, heap);
    if (heap == (void *) -1)
        return NULL;
    memset(heap, 0, new_size);
    return heap;
}

static block_t *init_block(block_t *ptr, size_t sz, block_t *list) {
    *ptr = (block_t) {
            .sz = sz,
            .next = NULL, .prev = NULL,
            .metadata = BLOCK_OFFSET(ptr)};
    (*ptr->metadata) = (metadata_t) {
            .sz = sz - MIN_METADATA_SZ,
            .next = NULL, .prev = NULL,
            .free = true};
    if (list) {
        ptr->prev = list;
//        ptr->next = list->next;
        list->next = ptr;
    }
    return ptr;
}


INTERNAL bool add_in_block_list(block_t **p_list, block_t *ptr, size_t sz) {
    block_t *list = *p_list;

    if (!list) {
        *p_list = init_block(ptr, sz, NULL);
//        dbg_pf("[ADD BLOCK - ARENA INIT] %p,\tSize: %zd",
//               *p_list, (*p_list)->sz);
//        dbg_pf("[ADD BLOCK - ARENA INIT] METADATA - Ptr: %p,\tSize: %zd",
//               (*p_list)->metadata, (*p_list)->metadata->sz);
        return true;
    }
    for (; list->next; list = list->next);
    init_block(ptr, sz, list);
//    list->next = init_block(ptr, sz, list);
    dbg_pf("[ ADD BLOCK LOOP ==> END ]: %p", list);
//    dbg_pf("[ADD BLOCK - ARENA INIT] METADATA - Ptr: %p,\tSize: %zd",
//            list->metadata, list->metadata->sz);
    return true;
}