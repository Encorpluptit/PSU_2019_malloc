#ifndef PSU_2019_MALLOC_MEMORY_H
#define PSU_2019_MALLOC_MEMORY_H

#include <stddef.h>

void *malloc(size_t size);
void *realloc(size_t nmemb, size_t size);
void *calloc(void *ptr, size_t size);
void free(void *ptr);

void hello(void);

#endif //PSU_2019_MALLOC_MEMORY_H
