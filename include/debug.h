/*
** EPITECH PROJECT, 2020
** Malloc
** File description:
** Header file fo debug maccro
*/

#ifndef PSU_2019_MALLOC_DEBUG_H
#define PSU_2019_MALLOC_DEBUG_H

#ifdef _DEBUG_

#include <stdio.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ?  \
                        strrchr(__FILE__, '/') + 1 : __FILE__)

#define dbg(x) write(1, x"\n", sizeof(x))

#define dbg_local                                   \
    (printf("[ %s ] - [ %s():%d ] ==> ",            \
            __FILENAME__,                           \
            __func__,                               \
            __LINE__))

#define dbg_pf(x, ...)                              \
    dbg_local;                                      \
    printf(x"\n", __VA_ARGS__);

#define dbg_begin(of, x, ...)                           \
    dbg_local;                                          \
    printf("[ begin: %s]\t"x"\n", of, __VA_ARGS__)

#define dbg_end(of, x, ...)                             \
    dbg_local;                                          \
    printf("[ end: %s]\t"x"\n", of, __VA_ARGS__)

#define dbg_loop(count, x, ...)                             \
    dbg_local;                                              \
    printf("[ %d ]\t"x"\n", count, __VA_ARGS__)

#define dbg_beginf(x, ...) dbg_begin("func", x, __VA_ARGS__)
#define dbg_endf(x, ...) dbg_end("func", x, __VA_ARGS__)


#else

#include <stdio.h>
#include <string.h>

#define dbg(x) write(1, x"\n", sizeof(x))
#define dbg_pf(x, ...)
#define dbg_begin(of, x, ...)
#define dbg_end(of, x, ...)
#define dbg_loop(of, x, ...)
#define dbg_beginf(x, ...)
#define dbg_endf(x, ...)

#define dbg_p(x, ...)                              \
    printf(x"\n", __VA_ARGS__);
//    dbg_local;
#endif /* _DEBUG_ */

#endif //PSU_2019_MALLOC_DEBUG_H
