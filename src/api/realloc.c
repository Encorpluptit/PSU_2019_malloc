//
// Created by dbernard on 2/10/20.
//

#include <string.h>
#include "my_malloc.h"

void *my_realloc(void *ptr, size_t sz) {
    void *new_ptr = NULL;

    if (!ptr)
        return my_malloc(sz);
    if (!(new_ptr = my_malloc(sz)))
        return NULL;
    memcpy(new_ptr, ptr, sz);
    my_free(ptr);
    return new_ptr;
}
