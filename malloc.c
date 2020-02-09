//
// Created by dbernard on 2/8/20.
//

#include "memory.h"

static metadata_t *find_best_metadata(block_t *block, size_t sz) {
    metadata_t *head = block->metadata;
    bool start = true;

    for (metadata_t *tmp = head; tmp != head || start; tmp = tmp->next) {
        dbg_pf("[ BEST DATA SIZE ]: %zd", tmp->sz);
        if (tmp->free && tmp->sz >= sz)
            return tmp;
        start = false;
    }
//    for (metadata_t *tmp = block->metadata; tmp != head; tmp = tmp->next) {
//        dbg_pf("[ BEST DATA SIZE ]: %zd", tmp->sz);
//        if (tmp->free && tmp->sz >= sz)
//            return tmp;
//    }
//    for (metadata_t *tmp = block->metadata; tmp->next; tmp = tmp->next)
//        if (tmp->sz >= sz)
//            return tmp;
    return NULL;
}

void *my_malloc(size_t sz) {
    sz = sz < 32 ? 32 + METADATA_H_SZ : sz + METADATA_H_SZ;
//    sz = sz < 32 ? 32 + METADATA_H_SZ : sz + METADATA_H_SZ;
    block_t *head = arena_control();
    bool start = true;
    block_t *tmp = head;
    metadata_t *res = NULL;

    dbg_pf("[ MALLOC SIZE ]: %zd", sz);
    dbg_pf("%p", head ? head : NULL);
//    for (block_t *tmp = head; tmp && (tmp != head || start); tmp = tmp->next) {
    for (; (tmp != head || start); tmp = tmp->next) {
        dbg("LOOP !!!!");
        if ((res = find_best_metadata(tmp, sz))) {
            dbg_pf("FOUND !!!! : %p\t%zd", res, res->sz);
            break;
        }
        start = false;
    }
    if (tmp != head || start) {
        for (; res->sz >= sz * 2; )
            split_block(&res);
        res->free = false;
        return METADATA_OFFSET(res);
    }

    return NULL;
}