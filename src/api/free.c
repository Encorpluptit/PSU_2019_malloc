//
// Created by dbernard on 2/9/20.
//

#include "memory.h"

metadata_t *find_ptr(void *ptr) {
    metadata_t *mdata = NULL;
    block_t *head = arena_control();

//    for (block_t *blck = head; blck; blck = blck->next)
    for (block_t *blck = arena_control(); blck; blck = blck->next)
        for (mdata = blck->metadata; mdata; mdata = mdata->next) {
//            dbg_pf("[ FREE ] MDATA: %p, \t PTR: %p", mdata, ptr);
            dbg_pf("[ FREE ] MDATA: %p, \t PTR: %p", METADATA_OFFSET(mdata), ptr);
            if (METADATA_OFFSET(mdata) == ptr) {
                dbg("BREAK!");
                return mdata;
            }
        }
    return NULL;
}

void my_free(void *ptr) {
    metadata_t *mdata = NULL;

    if (!ptr)
        return;
    mdata = find_ptr(ptr);
    if (!mdata)
        return;
    mdata->free = true;
    merge_metadata(mdata, mdata->next);
}