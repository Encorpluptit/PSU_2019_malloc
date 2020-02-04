#ifndef PSU_2019_MALLOC_MEMORY_H
#define PSU_2019_MALLOC_MEMORY_H

#include <stddef.h>

typedef struct ptr_s ptr_t;
struct ptr_s {
    ptr_t *next;
    ptr_t *prev;
    char data[1];
};

void *malloc(size_t size);
void *realloc(size_t nmemb, size_t size);
void *calloc(void *ptr, size_t size);
void free(void *ptr);

void hello(void);

#endif //PSU_2019_MALLOC_MEMORY_H
