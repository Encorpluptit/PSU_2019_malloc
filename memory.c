//#define _GNU_SOURCE
#include <assert.h>
#include <unistd.h>
#include "memory.h"
#include <stdio.h>
#include <stdbool.h>

//inline size_t align(size_t sz) {
//    return (sz + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
//}

//ctrl_t *init_control() {
//    static ctrl_t control = {0};
//    static ptr_t alloc;
//    static ptr_t free;
//
//    control.alloc = &alloc;
//    control.free = &free;
//    return &control;
//}

void *request_block() {
    void *heap = sbrk(0);
    if (brk(heap + (PAGE_SZ)) == -1)
        return NULL;
    return heap + (PAGE_SZ);
}

ctrl_t *arena_control() {
    static ctrl_t control = {0};
    void *heap = NULL;

    if (control.alloc && control.free)
        return &control;
    write(1, "Init Arena\n", 11);
    for (uint8_t i = 1; i <= 10; ++i) {
        heap = request_block();
        dbg("<== [ Init Arena Control Loop ] ==>");
        if (!add_in_list(&control.free, heap))
            return NULL;
        if (!add_in_list(&control.alloc, heap))
            return NULL;
    }
    dbg("<== [ Init Arena Control Loop  {{ END }}] ==>");
//    heap = sbrk(0);
//        if (brk(heap + (PAGE_SZ)) == -1)
//            return NULL;
    dbg("<== [ Init Arena Control {{ END }}] ==>");
    return &control;
}
//bool add_in_list(ptr_t **p_list, void *p_ptr) {
//    ptr_t *list = *p_list;
//    uintptr_t *ptr = p_ptr;
//
//    for (list = )
//    return true;
//}
//
//ctrl_t *arena_control() {
//    static ctrl_t control = {0};
//    void *heap = NULL;
//
//    if (control.alloc && control.free)
//        return &control;
//    write(1, "Init Arena\n", 11);
//    for (uint8_t i = 1; i <= 10; ++i) {
//        heap = request_block();
////        if (!add_in_list(&control.free, heap))
////            return NULL;
//        write(1, "YO\n", 3);
//    }
////    heap = sbrk(0);
////        if (brk(heap + (PAGE_SZ)) == -1)
////            return NULL;
//    write(1, "END: Init Arena\n", 16);
//    return &control;
//}

ptr_t **get_arena_alloc() {
    return &arena_control()->alloc;
}

ptr_t **get_arena_free() {
    return &arena_control()->free;
}

bool insert_into(ptr_t *new_ptr, size_t size) {
    ptr_t **head = get_arena_alloc();
    ptr_t *tmp = NULL;

//    if (!*head) {
//        write(1, "first\n", 6);
//        *head = new_ptr;
//        (*head)->next = new_ptr;
//        (*head)->prev = new_ptr;
//        return true;
//    }
    dbg("==[ INSERT INTO ] ==");
//    tmp = (*head)->prev;
//    write(1, tmp ? "OUI\n" : "NON\n", 4);
//    write(1, new_ptr ? "OUI\n" : "NON\n", 4);
//    (*head)->prev = new_ptr;
//    tmp->next = new_ptr;
//    write(1, "Insert\n", 7);
//    (*head)->prev = new_ptr;
//    (*head)->size = size;
//    write(1, "Insert\n", 7);
    return true;
}



//ptr_t *get_arena_alloc(bool give) {
//    static ptr_t control = {0};
//
//    if (give)
//        return &control;
//    control = *ptr;
//    return &control;
//}
//
//void hello(void) {
//    printf("Hello, World!\n");
//}

int main() {
    malloc((1));
    ptr_t **test = get_arena_free();

    for (ptr_t *tmp = *test; tmp && tmp->next != *test; tmp = tmp->next)
        dbg("FINAL FREE LIST");

    return 0;
}

//int main(void) {
////    void *b = sbrk(0);
////    int *p = (int *) b;
////
////    /* Move it 2 ints forward */
////    brk(p + 3);
////
////    /* Use the ints. */
////    *p = 1;
////    *(p + 1) = 2;
////    *(p + 2) = 4;
////    printf("YO\n");
////    printf("%d, %d, %d\n", *p, *(p + 1), *(p + 2));
////    assert(*p == 1);
////    assert(*(p + 1) == 2);
////
////    /* Deallocate back. */
////    brk(b);
////    write(1, "main\n", 5);
//    char *lol = malloc(10000);
//    for (size_t c = 0; c < 9999; ++c)
//        lol[c] = '1';
//    lol[9999] = '\n';
//    write(1, lol, 10000);
//    char *lol2 = malloc(100);
//    for (__uint8_t c = 0; c < 99; ++c)
//        lol2[c] = '2';
//    lol2[99] = '\n';
//    write(1, lol2, 100);
//    write(1, lol, 10000);
//    return 0;
//}
