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
void *malloc(size_t sz);

void *calloc(size_t nmem, size_t sz);

void *realloc(void *ptr, size_t sz);

void *reallocarray(void *ptr, size_t nmemb, size_t sz);

void free(void *ptr);

#endif //PSU_2019_MALLOC_MY_MALLOC_H
