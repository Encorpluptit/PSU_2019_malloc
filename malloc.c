//
// Created by dbernard on 2/4/20.
//

#include <stdio.h>
#include "memory.h"

//void *malloc(size_t size) {
//    ptr_t *new_page = NULL;
//    void *heap = sbrk(0);
//
//    //faire un multiple de 128;
//    brk(heap + size);
//    new_page = heap + sizeof(ptr_t);
//    insert_into(new_page, size);
//    write(1, "malloc\n", 7);
//    return heap;
//}

static size_t align(size_t sz) {
    return (sz + sizeof(ptr_t) - 1) & ~(sizeof(ptr_t) - 1);
}

void *my_malloc(size_t size) {
    ptr_t **free_head = get_arena_free();
    ptr_t *tmp = NULL;
    size_t aligned_sz = align(size);
    printf("%zd,\t%zd\n", size, aligned_sz);

    for (tmp = *free_head; tmp->next != *free_head && tmp->size < aligned_sz; tmp = tmp->next)
        dbg("<== [ MALLOC LOOP ON FREE LIST ] ==>");
    if (tmp->size >= aligned_sz) {
        dbg("<== [ FIRST FIT ] ==>");
        return tmp->user_ptr;
    }
    return tmp->user_ptr;
}
