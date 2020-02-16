/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** Source file for free.
*/

#include "my_malloc.h"
#include "internal.h"

void my_free(void *ptr)
{
    mdata_t *mdata = NULL;

    if (!ptr)
        return;
    mdata = find_ptr(ptr);
    if (!mdata)
        return;
    dbg_pf("FREE: %zd", mdata->sz);
    mdata->free = true;
    merge_mdata(mdata);
    dbg_pf("FREE: %zd", mdata->sz);
}
