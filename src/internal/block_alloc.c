/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** [INTERNAL] Source file for block alloc.
*/

#include <string.h>
#include "my_malloc.h"
#include "internal.h"

INTERNAL void *request_block(size_t sz)
{
    size_t new_size = sz;
    void *heap = sbrk(new_size);

    if (heap == (void *) -1)
        return NULL;
    memset(heap, 0, new_size);
    return heap;
}

static block_t *init_block(block_t *ptr, size_t sz, block_t *list)
{
    *ptr = (block_t) {
            .sz = sz, .next = NULL, .prev = NULL,
            .mdata = BLOCK_OFFSET(ptr)};
    (*ptr->mdata) = (mdata_t) {
            .sz = sz - MIN_METADATA_SZ, .free = true,
            .next = NULL, .prev = NULL};
    if (list) {
        ptr->prev = list;
        list->next = ptr;
    }
    return ptr;
}

INTERNAL bool add_in_block_list(block_t **p_list, block_t *ptr, size_t sz)
{
    block_t *list = *p_list;

    if (!list) {
        *p_list = init_block(ptr, sz, NULL);
        return true;
    }
    for (; list->next; list = list->next);
    init_block(ptr, sz, list);
    return true;
}
