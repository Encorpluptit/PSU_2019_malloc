//
// Created by dbernard on 2/10/20.
//

#include <string.h>
#include "my_malloc.h"

void *realloc(void *ptr, size_t sz) {
    void *new_ptr = NULL;

    if (!ptr)
        return malloc(sz);
    if (!(new_ptr = malloc(sz)))
        return NULL;
    memcpy(new_ptr, ptr, sz);
    free(ptr);
    return new_ptr;
}
