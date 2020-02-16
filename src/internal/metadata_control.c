/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** [INTERNAL] Source file for control metadata split and merge.
*/

#include <string.h>
#include "my_malloc.h"
#include "internal.h"

INTERNAL bool split_mdata(mdata_t **p_mdata)
{
    mdata_t *mdata = *p_mdata;
    size_t offset = align(mdata->sz / 2);
    mdata_t *new_mdata = (mdata_t *) ((uintptr_t) mdata + offset);

    if ((*p_mdata)->sz <= MIN_METADATA_SZ)
        return false;
    dbg_pf("SIZE SPLIT: Offset: %zd\t Old/new Ptr: %p/%p",
           offset, mdata, new_mdata);
    size_t sz_tmp = mdata->sz;
    (*new_mdata) = (mdata_t) {
            .sz = mdata->sz - offset, .free = true,
            .prev = mdata, .next = mdata->next};
    (*mdata) = (mdata_t) {
            .sz = offset - METADATA_H_SZ, .free = true,
            .prev = mdata->prev, .next = new_mdata};
    dbg_pf("SPLIT DIFF: %zd", (uintptr_t) new_mdata - (uintptr_t) mdata);
    dbg_pf("SIZE: ori: %zd, \tsum: %zd,\tcurr: %zd,\tnew: %zd",
           sz_tmp, mdata->sz + new_mdata->sz + METADATA_H_SZ,
           mdata->sz, new_mdata->sz);
    return true;
}

INTERNAL bool merge_mdata(mdata_t *mdata)
{
    if (!mdata || !mdata->free)
        return false;
    if (mdata->prev)
        return merge_mdata(mdata->prev);
    if (!mdata->next || !mdata->next->free)
        return false;
    dbg_pf("MERGE: %zd\tTO MERGE: %zd + %zd = %zd ===> SUM: %zd",
           mdata->sz, mdata->next->sz,
           METADATA_H_SZ, mdata->next->sz + METADATA_H_SZ,
           mdata->sz + mdata->next->sz + METADATA_H_SZ);
    if (mdata->next->next)
        mdata->next->next->prev = mdata;
    mdata->sz += mdata->next->sz + METADATA_H_SZ;
    mdata->next = mdata->next->next;
    memset(METADATA_OFFSET(mdata), 0, mdata->sz);
    return merge_mdata(mdata->next);
}
