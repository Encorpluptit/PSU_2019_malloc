//#define _GNU_SOURCE
#include <assert.h>
#include <unistd.h>
#include "memory.h"
#include <stdio.h>
#include <stdbool.h>

//inline size_t align(size_t sz) {
//    return (sz + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
//}

void *request_block() {
    void *heap = sbrk(0);
    if (brk(heap + (PAGE_SZ)) == -1)
        return NULL;
    return heap;
}

ctrl_t *arena_control() {
    static ctrl_t control = {0};
    ptr_t *heap = NULL;

//    if (control.alloc && control.free) {
//        dbg("GIVE ARENA");
//        return &control;
//    }
    if (control.free) {
        dbg("GIVE ARENA");
        return &control;
    }
    for (uint8_t i = 1; i <= MALLOC_INIT_SZ; ++i) {
        heap = request_block();
        heap->size = PAGE_SZ - sizeof(ptr_t);
        heap->user_ptr = heap + sizeof(ptr_t);
        heap->free = true;
        printf("%p, %p\n", heap, heap->user_ptr);
        printf("%hhX, %hhX\n", (unsigned char)heap, (unsigned char)heap->user_ptr);
        dbg("<== [ Init Arena Control Loop ] ==>");
        if (!add_in_list(&control.free, heap))
            return NULL;
    }
    dbg("<== [ Init Arena Control {{ END }}] ==>");
    return &control;
}

ptr_t **get_arena_alloc() {
    return &arena_control()->alloc;
}

ptr_t **get_arena_free() {
    return &arena_control()->free;
}

int main() {
    ptr_t **head_free = get_arena_free();
    ptr_t *tmp = NULL;
    char *lol[10];

//    my_malloc((1));

//    dbg("FINAL FREE LIST");
//    for (tmp = *head_free; tmp && tmp->next != *head_free; tmp = tmp->next)
//        printf("%p\n", tmp);
//    if (tmp && tmp != *head_free)
//        printf("%p\n", tmp);
//    printf("HEAD ?: %p\n", tmp->next);

//    lol[0] = (*head_free)->user_ptr;
//    for (u_int64_t i = 0; i < 6000; ++i){
//        lol[0][i] = 'a';
//    }
//    lol[0][6000] = '\n';
//    write(1, lol[0], 6001);

    uint64_t index = 0;
    for (tmp = *head_free; tmp && tmp->next != *head_free; tmp = tmp->next) {
        lol[index] = tmp->user_ptr;
        for (u_int64_t i = 0; i < 6000; ++i)
            lol[index][i] = 'a';
        lol[index][6000] = '\n';
        write(1, lol[index], 6001);
        ++index;
    }
    if (tmp && tmp != *head_free) {
        lol[index] = tmp->user_ptr;
        for (u_int64_t i = 0; i < 6000; ++i)
            lol[index][i] = 'a';
        lol[index][6000] = '\n';
        write(1, lol[index], 6001);
    }

    char *test = my_malloc(6000);
    for (u_int64_t i = 0; i < 6000; ++i)
        test[i] = 'g';
    test[6000] = '\n';
    write(1, test, 6001);



//
//    for (tmp = *head_free; tmp && tmp->next != *head_free; tmp = tmp->next)
//        dbg("FINAL FREE LIST");
//    if (tmp && tmp != *head_free)
//        dbg("FINAL FREE LIST");
    ptr_t **free_end = get_arena_free();
    char *str = (*free_end)->user_ptr;
    write(1, str, 6001);
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
