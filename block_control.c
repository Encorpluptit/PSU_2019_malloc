//
// Created by dbernard on 2/8/20.
//

#include "memory.h"

//bool split_block(metadata_t **p_block) {
bool split_block(metadata_t **p_block, size_t offset) {
    metadata_t *block = *p_block;
//    size_t offset = align(block->sz / 2);
    metadata_t *new_block = (metadata_t *)((uintptr_t)block - METADATA_H_SZ + offset);

    dbg_pf("SIZE SPLIT: %zd\t Old/nex Ptr: %p/%p", offset, block, new_block);
    size_t sz_tmp = block->sz;
    block->sz -= offset;
    new_block->sz = block->sz + METADATA_H_SZ;
    new_block->next = block->next;
    new_block->free = true;
    new_block->user_ptr = METADATA_OFFSET(new_block);
    block->next = new_block;
//    new_block->sz = block->sz - METADATA_H_SZ;
    dbg_pf("SPLIT DIFF: %zd", (uintptr_t) new_block - (uintptr_t) block);
    dbg_pf("SIZE: ori: %zd, \tsum: %zd,\tcurr: %zd,\tnew: %zd",
            sz_tmp, block->sz + new_block->sz + METADATA_H_SZ, block->sz, new_block->sz);
//    *p_block = block;
    return true;
}