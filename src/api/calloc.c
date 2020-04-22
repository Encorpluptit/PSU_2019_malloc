/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** Source file for calloc.
*/

#include "my_malloc.h"

void *calloc(size_t nmem, size_t sz)
{
    return malloc(nmem * sz);
}
