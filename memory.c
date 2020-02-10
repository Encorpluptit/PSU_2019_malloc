//
// Created by dbernard on 2/8/20.
//

#include "memory.h"

char *fill_line(metadata_t *data, char **tab, size_t index) {
    for (size_t i = 0; i < data->sz; ++i)
        tab[index][i] = 'A' + (char) index;
    tab[index][data->sz - 3] = 'O';
    tab[index][data->sz - 2] = 'K';
    tab[index][data->sz - 1] = '\n';
    return (char *) (tab[index]) + data->sz - 4;
}

void test_memory(char **tab) {
    block_t *arena = arena_control();
    size_t index = 0;
    metadata_t *data = NULL;

    for (block_t *tmp = arena; tmp; tmp = tmp->next, ++index) {
        dbg_pf("[ FILL LINE BLOCK DUMP ] Ptr: %p,\tSize: %zd", tmp, tmp->sz);
        for (data = tmp->metadata; data; data = data->next) {
            dbg_pf("[ FILL LINE DATA DUMP ] Ptr: %p,\tSize: %zd\t User Ptr: %p,\tFree ? %s",
                   data, data->sz, METADATA_OFFSET(data), data->free ? "Y" : "N");
            dbg_pf("[ FILL LINE DATA DIFF PTR ]: %zd", (uintptr_t) data - (uintptr_t) tmp);
            tab[index] = METADATA_OFFSET(data);
            char *str = fill_line(data, tab, index);
            write(1, str, 4);
        }
    }
}

void simple_split(block_t *arena) {
    split_metadata(&arena->metadata);
    split_metadata(&arena->metadata->next);
    split_metadata(&arena->metadata->next->next);
    split_metadata(&arena->metadata->next);
}

void simple_merge(block_t *arena) {
    split_metadata(&arena->metadata);
    merge_metadata(arena->metadata, arena->metadata->next);
    split_metadata(&arena->metadata);
    merge_metadata(arena->metadata, arena->metadata->next);
}

void mass_merge(block_t *arena) {
    for (block_t *tmp = arena; tmp; tmp = tmp->next)
        for (metadata_t *m = tmp->metadata; m; m = m->next)
            while (split_metadata(&m));
    for (block_t *tmp = arena; tmp; tmp = tmp->next)
        merge_metadata(tmp->metadata, tmp->metadata->next);
}

void simple_malloc(void) {
    void *ptr = NULL;

    my_malloc(80);
    my_malloc(80);
    my_malloc(80);
    my_malloc(1000);
    my_malloc(1000);
    my_malloc(1000);
    my_malloc(1500);
    my_malloc(1500);
    my_malloc(3900);
    ptr = my_malloc(3900);
    dbg_pf("ptr: %p", ptr);
}

void big_one_malloc(void) {
    size_t limit = 50000;
    char *test = my_malloc(limit + 1);

    for (size_t i = 0; i < limit; ++i)
        test[i] = '&';
}

void smalls_free(void) {
//    size_t sz = MALLOC_INIT_SZ * 100;
    size_t sz = 3;
    char *tab[sz];

    for (size_t i = 0; i < sz; ++i)
        tab[i] = my_malloc(15);
    for (size_t i = 0; i < sz; ++i)
        my_free(tab[i]);
}

void smalls_malloc(void) {
    size_t sz = MALLOC_INIT_SZ * 70;
    char *tab[sz];

    for (size_t i = 0; i < sz; ++i) {
        tab[i] = my_malloc(15);
        tab[i] = (char *) {"<== OK ==>\n"};
    }
    for (size_t i = 0; i < sz; ++i)
        write(1, tab[i], strlen(tab[i]));
//    block_t *arena = arena_control();
//    merge_metadata(arena->metadata, arena->metadata->next);
}

int main() {
    block_t *arena = arena_control();
    char *tab[MALLOC_INIT_SZ] = {0};

    dbg_pf("[ IN MAIN ] ==> Ptr: %p,\tUser Ptr: %p,\tSize: %zd",
           arena, BLOCK_OFFSET(arena), arena->sz);
//    simple_split(arena);
//    simple_merge(arena);
//    mass_merge(arena);
//    simple_malloc();
//    smalls_malloc();
    smalls_free();
//    big_one_malloc();
    test_memory(tab);
    return 0;
}
