//
// Created by dbernard on 2/8/20.
//

#include "memory.h"

//bool split_block(metadata_t **p_block, size_t offset) {
bool split_block(metadata_t **p_block) {
    metadata_t *block = *p_block;
    size_t offset = align(block->sz / 2);
    metadata_t *new_block = (metadata_t *)((uintptr_t)block + offset);
//    metadata_t *new_block = (metadata_t *)((uintptr_t)block - (uintptr_t)(METADATA_H_SZ) + (uintptr_t)offset);

    dbg_pf("SIZE SPLIT: Offset: %zd\t Old/next Ptr: %p/%p", offset, block, new_block);
    size_t sz_tmp = block->sz;

    (*new_block) = (metadata_t) {
        .sz = block->sz - offset, .free = true,
        .next = block->next ? block->next : block,
        .prev = block->prev ? block->prev : block,};
//            .next = block->next,};
    (*block) = (metadata_t) {
        .sz = block->sz - offset, .free = true,
        .prev = block->prev ? block->prev : block,
            .next = new_block,};

    dbg_pf("SPLIT DIFF: %zd", (uintptr_t) new_block - (uintptr_t) block);
    dbg_pf("SIZE: ori: %zd, \tsum: %zd,\tcurr: %zd,\tnew: %zd",
            sz_tmp, block->sz + new_block->sz + 2 * METADATA_H_SZ, block->sz, new_block->sz);
//    *p_block = block;
    return true;
}

//
//bool merge_block(metadata_t **p_bloc) {
//    if (!(*p_bloc)->next && )
//}