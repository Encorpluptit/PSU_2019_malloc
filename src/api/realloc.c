/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** Source file for realloc.
*/

#include <string.h>
#include "my_malloc.h"
#include "internal.h"

mdata_t *check_ptr(void *ptr, size_t sz, bool *check)
{
    if (!sz) {
        free(ptr);
        *check = true;
        return NULL;
    }
    if (!ptr) {
        *check = true;
        if (!(ptr = malloc(sz)))
            return NULL;
        return GET_METADATA_PTR(ptr);
    }
    return GET_METADATA_PTR(ptr);
}

void *realloc(void *ptr, size_t sz)
{
    bool check = false;
    mdata_t *mdata = check_ptr(ptr, sz, &check);
    void *new_ptr = NULL;

    if (check) {
        if (!mdata)
            return NULL;
        return METADATA_OFFSET(mdata);
    }
    new_ptr = malloc(sz);
    memcpy(new_ptr, ptr, sz > mdata->sz ? mdata->sz : sz);
    free(ptr);
    return new_ptr;

}
