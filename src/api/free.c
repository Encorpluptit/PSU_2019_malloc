/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** Source file for free.
*/

#include "my_malloc.h"
#include "internal.h"

void free(void *ptr)
{
    mdata_t *mdata = NULL;

    if (!ptr)
        return;
    mdata = find_ptr(ptr);
    if (!mdata)
        return;
    mdata->free = true;
    merge_mdata(mdata);
}
