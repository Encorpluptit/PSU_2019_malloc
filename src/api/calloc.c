//
// Created by dbernard on 2/10/20.
//

#include <string.h>
#include "memory.h"

void *my_calloc(size_t nmem, size_t sz)
{
    void *ptr = my_malloc(nmem * sz);

    memset(ptr, 0, nmem * sz);
    return ptr;
}
