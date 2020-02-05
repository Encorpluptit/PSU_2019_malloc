//
// Created by dbernard on 2/5/20.
//

#include "memory.h"

bool add_in_list(ptr_t **p_list, void *p_ptr) {
    dbg("*Add in List begin function*");
    ptr_t *list = *p_list;
    ptr_t *tmp = NULL;

    if (!list) {
        dbg("INIT");
        *p_list = p_ptr;
        return true;
    }
    dbg("AFTER INIT");
    tmp = list->prev;
    list->prev = p_ptr;
    list->prev->next = *p_list;
    if (tmp)
        tmp->next = p_ptr;
    else
        (*p_list)->next = p_ptr;
    return true;
}