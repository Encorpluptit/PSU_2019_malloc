/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** Header file for external functions.
*/

#ifndef PSU_2019_MALLOC_MY_MALLOC_H
#define PSU_2019_MALLOC_MY_MALLOC_H

#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

#include "debug.h"
//(@TODO remove)


//<===============================================>
//<===============================================>
// API functions prototypes. (@TODO: TO CHANGE)
void *my_malloc(size_t sz);

void *my_calloc(size_t nmem, size_t sz);

void *my_realloc(void *ptr, size_t sz);

void *my_reallocarray(void *ptr, size_t nmemb, size_t sz);

void my_free(void *ptr);

#endif //PSU_2019_MALLOC_MY_MALLOC_H
