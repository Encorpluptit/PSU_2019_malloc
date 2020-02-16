/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** Source file for realloc.
*/

#include <string.h>
#include "my_malloc.h"
#include "internal.h"

void *my_realloc(void *ptr, size_t sz)
{
    void *new_ptr = NULL;
    metadata_t *mdata = NULL;

    if (!ptr)
        return my_malloc(sz);
    if (!(new_ptr = my_malloc(sz)))
        return NULL;
    mdata = GET_METADATA_PTR(ptr);
    memcpy(new_ptr, ptr, sz > mdata->sz ? mdata->sz : sz);
    my_free(ptr);
    return new_ptr;
}
