//
// Created by dbernard on 2/9/20.
//

#include "my_malloc.h"
#include "internal.h"

void free(void *ptr) {
    metadata_t *mdata = NULL;

    if (!ptr)
        return;
    mdata = find_ptr(ptr);
    if (!mdata)
        return;
    dbg_pf("FREE: %zd", mdata->sz);
    mdata->free = true;
    merge_metadata(mdata);
    dbg_pf("FREE: %zd", mdata->sz);
}