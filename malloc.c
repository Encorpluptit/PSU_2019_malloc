//
// Created by dbernard on 2/4/20.
//

#include <stdio.h>
#include "memory.h"

void *malloc(size_t size) {
    ptr_t *new_page = NULL;
    void *heap = sbrk(0);

    //faire un multiple de 128;
    brk(heap + size);
    new_page = heap + sizeof(ptr_t);
    insert_into(new_page, size);
    write(1, "malloc\n", 7);
    return heap;
}

//void *malloc(size_t size) {
//    void *heap = sbrk(0);
//
//    brk(heap + size);
//    ptr_t *new_page = heap;
//    insert_into(new_page);
//    write(1, "lol\n", 4);
//    return heap + sizeof(ptr_t);
//}
