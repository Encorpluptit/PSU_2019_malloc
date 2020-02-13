/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** [INTERNAL] Source file for finding ptr in malloc linked list.
*/

#include "my_malloc.h"
#include "internal.h"

INTERNAL metadata_t *find_ptr(void *ptr)
{
    metadata_t *mdata = NULL;

    for (block_t *blck = arena_control(); blck; blck = blck->next)
        for (mdata = blck->metadata; mdata; mdata = mdata->next)
            if (METADATA_OFFSET(mdata) == ptr) {
                dbg_pf("[ FREE ] MDATA: %p, \t PTR: %p", mdata, ptr);
                dbg_pf("[ FREE ] MDATA USER: %p, \t PTR: %p",
                    METADATA_OFFSET(mdata), ptr);
                return mdata;
            }
    return NULL;
}
