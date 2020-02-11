//
// Created by dbernard on 2/10/20.
//

#include <stdlib.h>
#include <stddef.h>
#include "memory.h"

void *my_realloc(void *ptr, size_t sz) {
    metadata_t *mdata = NULL;

    if (!ptr)
        return my_malloc(sz);
    dbg_pf("%p", ptr);
    if (!(mdata = find_ptr(ptr)))
        exit(37);
    mdata = (metadata_t *)GET_METADATA_PTR(mdata);
//    mdata = (metadata_t *) (uintptr_t) ptr - (uintptr_t) METADATA_H_SZ;
    dbg_pf("%p", mdata);
    dbg_pf("%zd", (size_t)mdata + offsetof(metadata_t, sz));
    return NULL;
}
