//
// Created by dbernard on 2/9/20.
//

#include "memory.h"

void free(void *ptr) {
    metadata_t *mdata = NULL;

    if (!ptr)
        return;
    mdata = find_ptr(ptr);
    if (!mdata)
        return;
    mdata->free = true;
    _merge_metadata(mdata);
//    merge_metadata(mdata, mdata->next);
}