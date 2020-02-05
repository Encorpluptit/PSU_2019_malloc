//
// Created by dbernard on 2/5/20.
//

#include "memory.h"

bool add_in_list(ptr_t **p_list, void *p_ptr) {
    dbg("*Add in List begin function*");
    ptr_t *list = *p_list;
    uintptr_t *ptr = p_ptr;


    if (!list) {
        dbg("INIT");
        *p_list = p_ptr;
//        (*p_list)->next = p_ptr;
//        (*p_list)->prev = p_ptr;
        return true;
    }
    if (!list->next && !list->prev) {
        dbg("SECOND INIT");

        (*p_list)->next = p_ptr;
        (*p_list)->prev = p_ptr;

    }

//    dbg(list->prev ? "PREV: OUI": "PREV: NON");
//    dbg(list->next ? "NEXT: OUI": "NEXT: NON");
//    for (; list && list->next && list->next != *p_list; list = list->next) {
//        write(1, "Add in list 3\n", 14);
//    }
//    list->next = p_ptr;
//    list->next->prev = *p_list;
    list->prev = p_ptr;
    list->prev->next = *p_list;
//    (*p_list)->prev = p_ptr;
//    for (ptr_t *tmp = *p_list; tmp != *p_list; tmp= tmp->next) {
//        write(1, "Add in list 3\n", 14);
//    }
//    if ()
//    write(1, "Add in list 4\n", 14);
    return true;
}