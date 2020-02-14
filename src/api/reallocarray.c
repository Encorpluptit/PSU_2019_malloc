/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** Source file for reallocarray.
*/

#include "my_malloc.h"

void *my_reallocarray(void *ptr, size_t nmemb, size_t sz)
{
    void *new_ptr = NULL;

    if (!ptr || !(new_ptr = my_malloc(sz * nmemb)))
        return NULL;
    memcpy(new_ptr, ptr, sz * nmemb);
    return new_ptr;
}
