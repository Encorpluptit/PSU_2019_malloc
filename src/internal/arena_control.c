/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** [INTERNAL] Source file for arena control.
*/

#include <stdlib.h>
#include "my_malloc.h"
#include "internal.h"

static void *init_arena(block_t *arena)
{
    block_t *heap = NULL;

    for (uint32_t i = 1; i <= MALLOC_INIT_SZ; ++i) {
        if (!(heap = request_block(PAGE_SZ)))
            return NULL;
        add_in_block_list(&arena, heap, PAGE_SZ);
    }
    return arena;
}

INTERNAL block_t *arena_control()
{
    static block_t *arena = NULL;

    if (!arena)
        if (!(arena = init_arena(arena)))
            exit(84);
    dbg_pf("GIVE ARENA: %p", arena);
    return arena;
}

INTERNAL int arena_get_page_size(void)
{
    static int page_sz = 0;

    if (!page_sz)
        page_sz = getpagesize();
    return page_sz;
}
