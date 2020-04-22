//
// Created by dbernard on 2/8/20.
//

#include "my_malloc.h"
#include "internal.h"

char *fill_line(mdata_t *data, char **tab, size_t index) {
    for (size_t i = 0; i < data->sz; ++i)
        tab[index][i] = 'A' + (char) (index);
    tab[index][data->sz - 3] = 'O';
    tab[index][data->sz - 2] = 'K';
    tab[index][data->sz - 1] = '\n';
    return (char *) (tab[index]) + data->sz - 4;
}

void test_memory(char **tab, bool rw) {
    block_t *arena = arena_control();
    size_t index = 0;
    mdata_t *data = NULL;

    for (block_t *tmp = arena; tmp; tmp = tmp->next, ++index) {
        dbg_pf("[ FILL LINE BLOCK DUMP ] Ptr: %p,\tSize: %zd\t INDEX: %zd", tmp, tmp->sz, index);
//        dbg_p("[ FILL LINE BLOCK DUMP ] Ptr: %p,\tSize: %zd\t INDEX: %zd", tmp, tmp->sz, index);
        for (data = tmp->mdata; data; data = data->next) {
//            dbg_p("[ FILL LINE DATA DUMP ] Ptr: %p,\tSize: %zd\t User Ptr: %p,\tFree ? %s",
//                   data, data->sz, METADATA_OFFSET(data), data->free ? "Y" : "N");
            write(1, data->free ? "Y\n" : "N\n", 2)
            dbg_pf("[ FILL LINE DATA DUMP ] Ptr: %p,\tSize: %zd\t User Ptr: %p,\tFree ? %s",
                   data, data->sz, METADATA_OFFSET(data), data->free ? "Y" : "N");
            dbg_pf("[ FILL LINE DATA DIFF PTR ]: %zd", (uintptr_t) data - (uintptr_t) tmp - BLOCK_H_SZ);
            if (rw) {
//                tab[index] = (char *) ((uintptr_t) data + METADATA_H_SZ);
                tab[index] = (char *) METADATA_OFFSET(data);
                char *str = fill_line(data, tab, index);
                write(1, str, 4);
            }
        }
    }
}

void simple_split(block_t *arena) {
    split_mdata(&arena->mdata);
    split_mdata(&arena->mdata->next);
    split_mdata(&arena->mdata->next->next);
    split_mdata(&arena->mdata->next);
}

void simple_merge(block_t *arena) {
    split_mdata(&arena->mdata);
    merge_mdata(arena->mdata);
    split_mdata(&arena->mdata);
    split_mdata(&arena->mdata->next);
    merge_mdata(arena->mdata);
}

void mass_merge(block_t *arena) {
    for (block_t *tmp = arena; tmp; tmp = tmp->next)
        for (mdata_t *m = tmp->mdata; m; m = m->next)
            while (split_mdata(&m));
    for (block_t *tmp = arena; tmp; tmp = tmp->next)
        merge_mdata(tmp->mdata);
}

void simple_malloc(void) {
    char *tab[MALLOC_INIT_SZ * 1000] = {0};


    tab[0] = malloc(80);
    tab[1] = malloc(80);
    tab[2] = malloc(80);
    tab[3] = malloc(1000);
    tab[4] = malloc(1000);
    tab[5] = malloc(1000);
    tab[6] = malloc(1500);
    tab[7] = malloc(1500);
    tab[8] = malloc(3900);
    tab[9] = malloc(3900);
    for (int i = 0; i < 10; ++i)
        free(tab[i]);
}

void big_one_malloc(void) {
    size_t limit = 50000;
    char *test = malloc(limit + 1);

    for (size_t i = 0; i < limit; ++i)
        test[i] = '&';
    free(test);
}

void big_malloc(void) {
    size_t limit = 50000;
    size_t loop = 50;
    char *tab[loop];

    for (size_t i = 0; i < loop; ++i) {
        tab[i] = malloc(limit);
        for (size_t j = 0; j < limit; ++j)
            tab[i][j] = '&';
    }
    for (size_t i = 0; i < loop; ++i)
        free(tab[i]);
}

void smalls_free(void) {
    size_t sz = MALLOC_INIT_SZ * 10;
//    size_t sz = 3;
    size_t malloc_size = 3000;
    char *tab[sz];

    for (size_t i = 0; i < sz; ++i) {
        tab[i] = malloc(malloc_size + 1);
        for (size_t j = 0; j < malloc_size; ++j)
            tab[i][j] = 'A';
        tab[i][malloc_size] = '\n';
        write(1, tab[i], malloc_size + 1);
    }
    for (size_t i = 0; i < sz; ++i)
        free(tab[i]);
    for (size_t i = 0; i < sz; ++i)
        tab[i] = malloc(malloc_size);
    for (size_t i = 0; i < sz; ++i)
        free(tab[i]);
}

void smalls_malloc(void) {
    size_t sz = MALLOC_INIT_SZ * 40;
    size_t malloc_sz = arena_get_page_size() / 2 - METADATA_H_SZ;
    char *tab[sz];

    for (size_t i = 0; i < sz; ++i) {
        tab[i] = malloc(malloc_sz + 1);
        for (size_t j = 0; j < malloc_sz; ++j)
            tab[i][j] = 'A';
        tab[i][malloc_sz] = '\n';
        write(1, tab[i], malloc_sz + 1);
    }
    for (size_t i = 0; i < sz; ++i)
        free(tab[i]);
}

void test_realloc() {
    size_t first_size = 10;
    size_t second_size = 5;
    char *test = malloc(first_size + 1);

    for (size_t i = 0; i < first_size; ++i)
        test[i] = 'A';
    test[first_size] = '\0';
    dbg_pf("[ TEST REALLOC ] INIT ==> Ptr: %p\tStr: %s", test, test);
    test = realloc(test, second_size + 1);
    dbg_pf("[ TEST REALLOC ] AFTER REALLOC ==> Ptr: %p\tStr: %s", test, test);
    for (size_t i = 0; i < second_size; ++i)
        test[i] = 'B';
    test[second_size] = '\0';
    dbg_pf("[ TEST REALLOC ] END ==> Ptr: %p\tStr: %s", test, test);
    free(test);
}

void test_realloc_array(void) {
    size_t first_size = 400;
    size_t second_size = 200;
    char *tab = malloc(first_size + 1);

    for (size_t i = 0; i < first_size; ++i)
        tab[i] = 'A';
    tab[first_size] = '\0';
    tab = reallocarray(tab, second_size, 1);
    for (size_t i = first_size; i < second_size; ++i)
        tab[i] = 'B';
    tab[second_size] = '\0';
    dbg_pf("%s", tab);

}

void smalls_pages(void) {
    size_t sz = 40;
    size_t malloc_sz = arena_get_page_size() / 2 - 1;
    char *tab[sz];

    for (size_t i = 0; i < sz; ++i) {
        tab[i] = malloc(malloc_sz + 1);
        for (size_t j = 0; j < malloc_sz; ++j)
            tab[i][j] = 'A';
        tab[i][malloc_sz] = '\n';
        write(1, tab[i], malloc_sz + 1);
    }
    for (size_t i = 0; i < sz - 1; ++i)
        free(tab[i]);
    tab[0] = malloc((malloc_sz) * 2 - 2);
    for (size_t i = 0; i < sz; ++i)
        free(tab[i]);
}


int main() {
    __attribute((unused))block_t *arena = arena_control();
    char *tab[MALLOC_INIT_SZ * 1000] = {0};
//    char **tab = malloc(MALLOC_INIT_SZ);

    dbg_pf("[ IN MAIN ] ==> Ptr: %p,\tUser Ptr: %p,\tSize: %zd",
           arena, BLOCK_OFFSET(arena), arena->sz);
//    simple_split(arena);
//    test_memory(tab, true);
//    simple_merge(arena);
//    test_memory(tab, true);
//    mass_merge(arena);
//    test_memory(tab, true);
//    simple_malloc();
//    test_memory(tab, true);
//    smalls_malloc();
//    test_memory(tab, true);
//    smalls_free();
//    test_memory(tab, true);
//    big_one_malloc();
//    test_memory(tab, true);
//    big_malloc();
//    test_memory(tab, true);
    smalls_pages();
    test_memory(tab, true);
//    test_realloc();
//    test_memory(tab, true);
//    test_realloc_array();
//    test_memory(tab, true);
    return 0;
}
