//
// Created by dbernard on 2/8/20.
//

#include "memory.h"

bool split_metadata(metadata_t **p_metadata) {
//    dbg_pf("SPLIT BEGIN SIZE: Offset: %zd", (*p_metadata)->sz);
    metadata_t *metadata = *p_metadata;
    size_t offset = align(metadata->sz / 2);
    metadata_t *new_metadata = (metadata_t *)((uintptr_t)metadata + offset);
//    metadata_t *new_metadata = (metadata_t *)((uintptr_t)metadata + offset + METADATA_H_SZ);
//    metadata_t *new_metadata = (metadata_t *)((uintptr_t)metadata  + offset - METADATA_H_SZ);

    if ((*p_metadata)->sz <= MIN_METADATA_SZ)
        return false;
    dbg_pf("SIZE SPLIT: Offset: %zd\t Old/next Ptr: %p/%p", offset, metadata, new_metadata);
    size_t sz_tmp = metadata->sz;
    (*new_metadata) = (metadata_t) {
        .sz = metadata->sz - offset, .free = true,
        .prev = metadata,
        .next = metadata->next,};
    (*metadata) = (metadata_t) {
        .sz = offset - METADATA_H_SZ, .free = true,
        .prev = metadata->prev,
        .next = new_metadata,};
    dbg_pf("SPLIT DIFF: %zd", (uintptr_t) new_metadata - (uintptr_t) metadata);
    dbg_pf("SIZE: ori: %zd, \tsum: %zd,\tcurr: %zd,\tnew: %zd",
           sz_tmp, metadata->sz + new_metadata->sz + METADATA_H_SZ, metadata->sz, new_metadata->sz);
//    *p_metadata = metadata;
    return true;
}


bool merge_metadata(metadata_t *metadata, metadata_t *to_merge) {
    if (!to_merge || !to_merge->free || !metadata || !metadata->free)
        return false;
//    dbg_pf("MERGE: %zd", to_merge->sz);
//    memset(METADATA_OFFSET(metadata), 0, metadata->sz);
    dbg_pf("MERGE: %zd\tTO MERGE: %zd", metadata->sz, to_merge->sz);
    metadata->next = to_merge->next;
    metadata->sz += to_merge->sz + METADATA_H_SZ;
    if (to_merge->next)
        to_merge->next->prev = metadata;
    dbg_pf("MERGED: %zd", metadata->sz);
    memset(METADATA_OFFSET(metadata), 0, metadata->sz);
//    memset(METADATA_OFFSET(metadata), 0, metadata->sz - METADATA_H_SZ);
//    memset(METADATA_OFFSET(metadata), 0, metadata->sz  + 2 * METADATA_H_SZ);
//    memset(to_merge, 0, (uintptr_t)to_merge->sz + METADATA_H_SZ);
//    memset(METADATA_OFFSET(metadata), 0, metadata->sz);
//    return (merge_metadata(metadata->prev, metadata) || merge_metadata(metadata, metadata->next));
    return (merge_metadata(metadata, metadata->next) || merge_metadata(metadata->prev, metadata));
//    return (merge_metadata(metadata, metadata->next) || merge_metadata(metadata->prev, metadata));
}
