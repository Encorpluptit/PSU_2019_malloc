//
// Created by dbernard on 2/4/20.
//

#include "memory.h"

void my_free(void **p_to_free) {
    ptr_t *to_free = *p_to_free - sizeof(ptr_t);
    ptr_t *tmp = NULL;

    ptr_t **head = get_arena_alloc();
    for (tmp = *head; tmp != to_free && tmp != *head; tmp = tmp->next);
    if (tmp == *head)
        return;

    return;;
}

