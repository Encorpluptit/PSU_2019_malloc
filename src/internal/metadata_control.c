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
    size_t sz_tmp = mdata->sz;
    (*new_mdata) = (mdata_t) {
            .sz = mdata->sz - offset, .free = true,
            .prev = mdata, .next = mdata->next};
    (*mdata) = (mdata_t) {
            .sz = offset - METADATA_H_SZ, .free = true,
            .prev = mdata->prev, .next = new_mdata};
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
    if (mdata->next->next)
        mdata->next->next->prev = mdata;
    mdata->sz += mdata->next->sz + METADATA_H_SZ;
    mdata->next = mdata->next->next;
    memset(METADATA_OFFSET(mdata), 0, mdata->sz);
    return merge_mdata(mdata->next);
}
