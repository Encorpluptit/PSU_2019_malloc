//
// Created by dbernard on 2/8/20.
//

#include "memory.h"

void fill_line(block_t *arena, char *TAB[]) {
    uint64_t index = 0;
    mdata_t *data = NULL;
    char *str = NULL;

    for (block_t *tmp = arena; tmp; tmp = tmp->next, ++index) {
        dbg_pf("[ FILL LINE BLOCK DUMP ] Ptr: %p,\tSize: %zd", tmp, tmp->sz);
        for (data = tmp->metadata; data; data = data->next) {
            dbg_pf("[ FILL LINE DATA DUMP ] Ptr: %p,\tSize: %zd\t User Ptr: %p", data, data->sz, data->user_ptr);
            TAB[index] = data->user_ptr;
            for (uint64_t i = 0; i < data->sz; ++i)
                TAB[index][i] = 'A' + (char)index;
            TAB[index][data->sz - 3] = 'O';
            TAB[index][data->sz - 2] = 'K';
            TAB[index][data->sz - 1] = '\n';
            str = (char *)(TAB[index]) + data->sz - 4;
            write(1, str, 3);
        }
    }
}


int main() {
    block_t *arena = arena_control();
    char *TAB[MALLOC_INIT_SZ] = {0};

    dbg_pf("[ IN MAIN ] ==> Ptr: %p,\tUser Ptr: %p,\tSize: %zd", arena, BLOCK_OFFSET(arena), arena->sz);
    fill_line(arena, TAB);
    return 0;
}