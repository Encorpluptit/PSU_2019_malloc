//
// Created by dbernard on 2/8/20.
//

#include "memory.h"

void fill_line(block_t *arena, char *TAB[]) {
    uint64_t index = 0;
    for (block_t *tmp = arena; tmp; tmp = tmp->next, ++index) {
        TAB[index] = BLOCK_OFFSET(tmp); //changer par metadata_user ptr
        dbg_pf("[ FILL LINE LOOP ]: Ptr: %p\tSize: %zd", tmp, tmp->sz);
        for (uint64_t i = 0; i < ((tmp->sz - 3) - sizeof(block_t)); ++i)
            TAB[index][i] = 'a';
        TAB[index][tmp->sz - sizeof(block_t) - 3] = 'O';
        TAB[index][tmp->sz - sizeof(block_t) - 2] = 'K';
        TAB[index][tmp->sz - sizeof(block_t) - 1] = '\n';
        char *str = (char *)(TAB[index]) + tmp->sz - sizeof(block_t) - 3;
        write(1, str, 3);
    }
}


int main() {
    block_t *arena = arena_control();
    char *TAB[MALLOC_INIT_SZ] = {0};
    fill_line(arena, TAB);
    dbg_pf("[ IN MAIN ] ==> Ptr: %p,\tUser Ptr: %p,\tSize: %zd", arena, BLOCK_OFFSET(arena), arena->sz);

    return 0;
}