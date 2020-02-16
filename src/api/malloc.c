/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** Source file for malloc.
*/

#include <stdlib.h>
#include "my_malloc.h"
#include "internal.h"

static void *malloc_block(block_t *arena, size_t sz)
{
    block_t *heap = request_block(sz);

    if (!heap)
        exit(84);
    dbg_pf("[ MALLOC WHOLE BLOCK SIZE ]: %zd", sz);
    add_in_block_list(&arena, heap, sz);
    return METADATA_OFFSET(heap->mdata);
}

static mdata_t *find_best_mdata(block_t *block, size_t sz)
{
    mdata_t *head = block->mdata;

    for (mdata_t *tmp = head; tmp; tmp = tmp->next) {
        dbg_pf("[ BEST DATA SIZE ]: %zd\t Requested: %zd", tmp->sz, sz);
        if (tmp->free && tmp->sz >= sz)
            return tmp;
    }
    return NULL;
}

static void *resize_mdata(mdata_t *mdata, size_t sz)
{
//    for (; mdata->sz >= align(sz);)
//    for (; mdata->sz > sz + METADATA_H_SZ;)
    for (; mdata->sz > sz;)
        split_mdata(&mdata);
    mdata->free = false;
    return METADATA_OFFSET(mdata);
}

void *my_malloc(size_t sz)
{
    size_t new_size  = align(sz + METADATA_H_SZ);
    block_t *head = arena_control();
    mdata_t *res = NULL;

    dbg_pf("[ MALLOC SIZE ]: %zd\tnew: %zd", sz, new_size);
    if (sz + MIN_METADATA_SZ > (size_t)PAGE_SZ)
        return malloc_block(head, new_size);
    for (block_t *tmp = head; tmp; tmp = tmp->next)
        if ((res = find_best_mdata(tmp, sz)))
            break;
    if (res)
        return resize_mdata(res, new_size - METADATA_H_SZ);
    malloc_block(head, PAGE_SZ);
    return my_malloc(sz);
}
