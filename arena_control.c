//
// Created by dbernard on 2/8/20.
//

#include <stdlib.h>
#include "memory.h"

static void *init_arena(block_t *arena) {
    block_t *heap = NULL;

    for (uint32_t i = 1; i <= MALLOC_INIT_SZ; ++i) {
        if (!(heap = request_block(PAGE_SZ)))
            return NULL;
        add_in_block_list(&arena, heap, PAGE_SZ);
    }
    return arena;
}

block_t *arena_control() {
    static block_t *arena = NULL;

    if (!arena) {
//        dbg_pf("ARENA NULL: %p", arena);
        if (!(arena = init_arena(arena)))
            exit(84);
//        dbg_pf("END INIT ARENA: %p,\t%p", arena, BLOCK_OFFSET(arena));
    }
    dbg_pf("GIVE ARENA: %p", arena);
    return arena;
}
