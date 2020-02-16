/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** [INTERNAL] Source file for finding ptr in malloc linked list.
*/

#include "my_malloc.h"
#include "internal.h"

INTERNAL mdata_t *find_ptr(void *ptr)
{
    mdata_t *mdata = NULL;

    for (block_t *blck = arena_control(); blck; blck = blck->next)
        for (mdata = blck->mdata; mdata; mdata = mdata->next)
            if (METADATA_OFFSET(mdata) == ptr)
                return mdata;
    return NULL;
}
