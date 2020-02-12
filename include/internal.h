//
// Created by dbernard on 2/11/20.
//

#ifndef PSU_2019_MALLOC_INTERNAL_H
#define PSU_2019_MALLOC_INTERNAL_H


#ifndef INTERNAL
#define INTERNAL
//#define INTERNAL __attribute__((visibility ("hidden"))) //(@TODO: fix compile errror)
#endif /* HIDDEN */


// size_control.c
INTERNAL size_t align(size_t sz);


// arena_control.c
INTERNAL block_t *arena_control();

INTERNAL int arena_get_page_size(void);


// block_alloc.c
INTERNAL bool add_in_block_list(block_t **list, block_t *ptr, size_t sz);

INTERNAL void *request_block(size_t sz);



// metadata_control.c
INTERNAL bool split_metadata(metadata_t **p_metadata);

INTERNAL bool merge_metadata(metadata_t *metadata);

// find_ptr.c
INTERNAL metadata_t *find_ptr(void *ptr);

#endif //PSU_2019_MALLOC_INTERNAL_H
