//
// Created by dbernard on 2/8/20.
//

#include "memory.h"

char *fill_line(metadata_t *data, char **TAB, size_t index) {
    for (size_t i = 0; i < data->sz; ++i)
        TAB[index][i] = 'A' + (char) index;
    TAB[index][data->sz - 3] = 'O';
    TAB[index][data->sz - 2] = 'K';
    TAB[index][data->sz - 1] = '\n';
    return (char *) (TAB[index]) + data->sz - 4;
}

void test_memory(block_t *arena, char **TAB) {
    size_t index = 0;
    metadata_t *data = NULL;

    for (block_t *tmp = arena;
         tmp && (!*TAB || tmp != arena);
         tmp = tmp->next, ++index) {
        dbg_pf("[ FILL LINE BLOCK DUMP ] Ptr: %p,\tSize: %zd", tmp, tmp->sz);
        bool start = true;
//        for (data = tmp->metadata; data != tmp->metadata || start; data = data->next) {
        for (data = tmp->metadata; (data && data != tmp->metadata) || start; data = data->next) {
//        for (data = tmp->metadata; data; data = data->next) {
            dbg_pf("[ FILL LINE DATA DUMP ] Ptr: %p,\tSize: %zd\t User Ptr: %p,\tFree ? %s",
                   data, data->sz, METADATA_OFFSET(data), data->free ? "Y" : "N");
            dbg_pf("[ FILL LINE DATA DIFF PTR ]: %zd", (uintptr_t) data - (uintptr_t) tmp);
            TAB[index] = METADATA_OFFSET(data);
            char *str = fill_line(data, TAB, index);
            write(1, str, 4);
            start = false;
        }
    }
}

void split(block_t *arena) {
    split_block(&arena->metadata);
    split_block(&arena->metadata->next);
//    split_block(&arena->metadata->next->next);
//    split_block(&arena->metadata->next);
}

void simple_malloc(void) {
    my_malloc(80);
    my_malloc(80);
    my_malloc(80);
    my_malloc(900);
    my_malloc(900);
    my_malloc(900);
    my_malloc(1500);
    my_malloc(1500);
    my_malloc(3900);
    void *ptr = my_malloc(3900);
    dbg_pf("ptr: %p", ptr);
}

void smalls_malloc(void) {
    for (size_t i  = 0; i < MALLOC_INIT_SZ * 50; ++i)
        my_malloc(1);
}

int main() {
    block_t *arena = arena_control();
    char *TAB[MALLOC_INIT_SZ] = {0};

    dbg_pf("[ IN MAIN ] ==> Ptr: %p,\tUser Ptr: %p,\tSize: %zd",
           arena, BLOCK_OFFSET(arena), arena->sz);
    split(arena);
//    simple_malloc();
//    smalls_malloc();
    test_memory(arena, TAB);
    return 0;
}
