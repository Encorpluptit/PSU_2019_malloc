//
// Created by dbernard on 2/8/20.
//

#include "memory.h"

static metadata_t *find_best_metadata(__attribute__((unused))block_t *block, __attribute__((unused))size_t sz) {
//    metadata_t *head = block->metadata;

    for (metadata_t *tmp = block->metadata; tmp; tmp = tmp->next) {
        dbg_pf("[ BEST DATA SIZE ]: %zd", tmp->sz);
        if (tmp->sz >= sz)
            return tmp;
    }
//    for (metadata_t *tmp = block->metadata; tmp->next; tmp = tmp->next)
//        if (tmp->sz >= sz)
//            return tmp;
    return NULL;
}

void *my_malloc(size_t sz) {
    sz = sz < 32 ? 32 + METADATA_H_SZ : align(sz - METADATA_H_SZ);
    block_t *head = arena_control();
    bool start = true;
    block_t *tmp = head; metadata_t *res = NULL;

    dbg_pf("[ MALLOC SIZE ]: %zd", sz);
    dbg_pf("%p", head ? head : NULL);
//    for (block_t *tmp = head; tmp && (tmp != head || start); tmp = tmp->next) {
    for (; (tmp != head || start); tmp = tmp->next) {
        dbg("LOOP !!!!");
        if ((res = find_best_metadata(tmp, sz))) {
            dbg_pf("FOUND !!!! : %p", res);
            break;
        }
//        if (find_best_metadata(tmp, sz))
//            break;
        start = false;
    }
    if (tmp != head || start) {
        dbg("Yes !!!!");
        split_block(&res, sz);
    }

    return NULL;
}