/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** Source file for calloc.
*/

#include <string.h>
#include "my_malloc.h"

void *my_calloc(size_t nmem, size_t sz)
{
    return malloc(nmem * sz);
}
