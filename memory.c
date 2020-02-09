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
        for (data = tmp->metadata; data; data = data->next) {
            dbg_pf("[ FILL LINE DATA DUMP ] Ptr: %p,\tSize: %zd\t User Ptr: %p",
                   data, data->sz, METADATA_OFFSET(data));
            dbg_pf("[ FILL LINE DATA DIFF PTR ]: %zd", (uintptr_t) data - (uintptr_t) tmp);
            TAB[index] = METADATA_OFFSET(data);
            char *str = fill_line(data, TAB, index);
            write(1, str, 4);
        }
    }
}

//void test_memory(block_t *arena, char **TAB) {
//    size_t index = 0;
//    metadata_t *data = NULL;
//
//    for (block_t *tmp = arena;
//         tmp && (!*TAB || tmp != arena);
//         tmp = tmp->next, ++index) {
//        dbg_pf("[ FILL LINE BLOCK DUMP ] Ptr: %p,\tSize: %zd", tmp, tmp->sz);
//        for (data = tmp->metadata; data; data = data->next) {
//            dbg_pf("[ FILL LINE DATA DUMP ] Ptr: %p,\tSize: %zd\t User Ptr: %p",
//                   data, data->sz, data->user_ptr);
//            dbg_pf("[ FILL LINE DATA DIFF PTR ]: %zd", (uintptr_t) data - (uintptr_t) tmp);
//            TAB[index] = data->user_ptr;
//            char *str = fill_line(data, TAB, index);
//            write(1, str, 4);
//        }
//    }
//}
//
void split_test(block_t *arena) {
    split_block(&arena->metadata);
    split_block(&arena->metadata);
    split_block(&arena->metadata);
    split_block(&arena->metadata);
    split_block(&arena->metadata);
//    split_block(&arena->metadata->next);
//    split_block(&arena->metadata, align(400));
//    split_block(&arena->metadata->next, align(900));
//    split_block(&arena->metadata, align(arena->metadata->sz / 2));
//    split_block(&arena->metadata, align(arena->metadata->sz / 2));
//    split_block(&arena->metadata, align(arena->metadata->sz / 2));
//    split_block(&arena->metadata, align(arena->metadata->sz / 2));
//    split_block(&arena->metadata, align(arena->metadata->sz / 2));
//    split_block(&arena->metadata, align(arena->metadata->sz / 2));
//    split_block(&arena->metadata, align(arena->metadata->sz / 2));
//    split_block(&arena->metadata, align(arena->metadata->sz / 2));
//    split_block(&arena->metadata, align(arena->metadata->sz / 2));
}

int main() {
    block_t *arena = arena_control();
    char *TAB[MALLOC_INIT_SZ] = {0};

    dbg_pf("[ IN MAIN ] ==> Ptr: %p,\tUser Ptr: %p,\tSize: %zd",
           arena, BLOCK_OFFSET(arena), arena->sz);
    my_malloc(80);
    my_malloc(80);
//    split_test(arena);
    test_memory(arena, TAB);
    return 0;
}
