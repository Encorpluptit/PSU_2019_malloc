/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** [INTERNAL] Source file for control metadata split and merge.
*/

#include <string.h>
#include "my_malloc.h"
#include "internal.h"

INTERNAL bool split_metadata(metadata_t **p_metadata)
{
    metadata_t *metadata = *p_metadata;
    size_t offset = align(metadata->sz / 2);
    metadata_t *new_metadata = (metadata_t *) ((uintptr_t) metadata + offset);

    if ((*p_metadata)->sz <= MIN_METADATA_SZ)
        return false;
    dbg_pf("SIZE SPLIT: Offset: %zd\t Old/new Ptr: %p/%p",
            offset, metadata, new_metadata);
    size_t sz_tmp = metadata->sz;
    (*new_metadata) = (metadata_t) {
            .sz = metadata->sz - offset, .free = true,
            .prev = metadata, .next = metadata->next};
    (*metadata) = (metadata_t) {
            .sz = offset - METADATA_H_SZ, .free = true,
            .prev = metadata->prev, .next = new_metadata};
    dbg_pf("SPLIT DIFF: %zd", (uintptr_t) new_metadata - (uintptr_t) metadata);
    dbg_pf("SIZE: ori: %zd, \tsum: %zd,\tcurr: %zd,\tnew: %zd",
            sz_tmp, metadata->sz + new_metadata->sz + METADATA_H_SZ,
            metadata->sz, new_metadata->sz);
    return true;
}

INTERNAL bool merge_metadata(metadata_t *metadata)
{
    if (!metadata || !metadata->free)
        return false;
    if (metadata->prev)
        return merge_metadata(metadata->prev);
    if (!metadata->next || !metadata->next->free)
        return false;
    dbg_pf("MERGE: %zd\tTO MERGE: %zd + %zd = %zd ===> SUM: %zd",
            metadata->sz, metadata->next->sz,
            METADATA_H_SZ, metadata->next->sz + METADATA_H_SZ,
            metadata->sz + metadata->next->sz + METADATA_H_SZ);
    if (metadata->next->next)
        metadata->next->next->prev = metadata;
    metadata->sz += metadata->next->sz + METADATA_H_SZ;
    metadata->next = metadata->next->next;
    memset(METADATA_OFFSET(metadata), 0, metadata->sz);
    return merge_metadata(metadata->next);
}
