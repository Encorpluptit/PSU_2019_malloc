//
// Created by dbernard on 2/8/20.
//

#include <stdlib.h>
#include "memory.h"

static void *malloc_block(block_t *arena, size_t sz) {
    sz = align(sz + MIN_METADATA_SZ);
    block_t *heap = request_block(sz);

    if (!heap)
        exit(84);
    dbg_pf("[ MALLOC WHOLE BLOCK SIZE ]: %zd", sz);
    add_in_block_list(&arena, heap, sz);
    return METADATA_OFFSET(heap->metadata);
}

static metadata_t *find_best_metadata(block_t *block, size_t sz) {
    metadata_t *head = block->metadata;

    for (metadata_t *tmp = head; tmp; tmp = tmp->next) {
        dbg_pf("[ BEST DATA SIZE ]: %zd", tmp->sz);
        if (tmp->free && tmp->sz >= sz)
            return tmp;
    }
    return NULL;
}

static void *resize_metadata(metadata_t *metadata, size_t sz) {
//    for (; metadata->sz >= align(sz);)
    for (; metadata->sz > sz + METADATA_H_SZ;)
//    for (; metadata->sz > sz;)
        split_metadata(&metadata);
    metadata->free = false;
    return METADATA_OFFSET(metadata);
}

void *malloc(size_t sz) {
    sz = align(sz + METADATA_H_SZ);
    block_t *head = arena_control();
    metadata_t *res = NULL;

    dbg_pf("[ MALLOC SIZE ]: %zd", sz);
    if (sz + MIN_METADATA_SZ > (size_t) PAGE_SZ)
        return malloc_block(head, sz);
    for (block_t *tmp = head; tmp; tmp = tmp->next)
        if ((res = find_best_metadata(tmp, sz)))
            break;
    if (res)
        return resize_metadata(res, sz);
    malloc_block(head, PAGE_SZ);
    return malloc(sz);
}