/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** Header for attributes, defines, includes, typedef, ... .
*/

//<===========================================================================>
// GCC ATRRIBUTES.
#ifndef __USED_GCC_ATTRIBUTES_H__
#define __USED_GCC_ATTRIBUTES_H__


/* // ATTRIBUTE BASE MACRO */
#define __a(args...)            __attribute__(args)

#define __packed                __a((packed))
#define __transparent           __a((__transparent_union__))

//FUNCTIONS ATTRIBUTES
#define __visibility(args...)   __a((visibility(args)))
#define __hidden                __visibility("hidden")
#define __destructor            __a((destructor))
#define __constructor           __a((constructor))

/* //VARIABLES ATTRIBUTES */
#define __unused                __a((unused))
#define __cleanup(janitor)      __a((cleanup(janitor)))


#endif /* __USED_GCC_ATTRIBUTES_H__ */
//<===========================================================================>




//<===========================================================================>
// Personnals macros.
#ifdef __DEBUG_MACROS_H__
/* #define __DEBUG_MACROS_H__ */

#include <stdio.h>

#define dbg_local                               \
    (printf("[ %s ] - [ %s():%d ]",             \
            __FILE__,                           \
            __func__,                           \
            __LINE__))

#define dbg(x, ...)                             \
    dbg_local;                                  \
    printf(x"\n", __VA_ARGS__)

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
#define dbg(x, ...)
#define dbg_begin(of, x, ...)
#define dbg_end(of, x, ...)
#define dbg_loop(of, x, ...)
#define dbg_beginf(x, ...)
#define dbg_endf(x, ...)


#endif /* __DEBUG_MACROS_H__ */



//<===========================================================================>
// Personnals macros.
#ifndef __USED_MACROS_H__
#define __USED_MACROS_H__


// Custom free macro, to reset at NULL value.
#define FREE(x) free(x); x = NULL;

// Digit ascii value to numeric value
#define CTOI(c) ((int) ((c) - '0'))

// Numeric value to ascii char value
#define ITOC(i) ((char) ((i) + '0'))

// True if c is a printable ASCII char
#define CHAR_PRINTABLE(c) ((c) >= 32 && (c) <= 126)

// If an alphabetical character is lowercase, make it uppercase
#define CHAR_TO_UPPER(c)  ((c) >= 'a' && (c) <= 'z' ? (c) - 32 : (c))

// If an alphabetical character is uppercase, make it lowercase
#define CHAR_TO_LOWER(c)  ((c) >= 'A' && (c) <= 'Z' ? (c) - 32 : (c))

// Check if a pointer is NULL
#define IS_NULL(p) (!(p))

// Check if a char is an end of line (linebreak OR null char)
#define IS_EOL(c) ((c) == '\n' || (c) == '\0')

// Check if a char is strictly lowercase alphabetical
#define IS_ALPHA_LOW(c) ((c) >= 'a' && (c) <= 'z')

// Check if a char is strictly uppercase alphabetical
#define IS_ALPHA_UP(c) ((c) >= 'A' && (c) <= 'Z')

// Check if a char is strictly alphabetical
#define IS_ALPHA(c) (IS_ALPHALO(c) || IS_ALPHAUP(c))

// Check if a char is strictly numeric
#define IS_NUM(c) ((c) >= '0' && (c) <= '9')

// Check if a number is pair
#define IS_PAIR(n) !((n) % 2)

// Check if a number is odd
#define IS_ODD(n) ((n) % 2)

// Check if a char is strictly alphanumeric
#define IS_ALPHANUM(c) (IS_ALPHA(c) || IS_NUM(c))

// Check if a char is punctuation
#define IS_PUNCT(c)                                                \
    (                                                              \
        ((c) == '/')                                               \
        || ((c) == '\'') || ((c) == '\"')                          \
        || ((c) == ',') || ((c) == '.')                            \
        || ((c) == '?') || ((c) == '!')                            \
        || ((c) == ';') || ((c) == ':')                            \
        || ((c) == '(') || ((c) == ')')                            \
        || ((c) == '-')                                            \
    )                                                              \


// Check if a char is a minus sign (-)
#define IS_MINUS(c) (c == '-')

// Check if a char is a sign (+ OR -)
#define IS_SIGN(c) ((c) == '+' || IS_MINUS(c))

// Check if a char is a percent (%)
#define IS_PERCENT(c) ((c) == '%')

// Check if a char is a mul or div (* OR / OR %)
#define IS_MUL_DIV(c) ((c) == '*' || (c) == '/' || IS_PERCENT(c))

// Check if a char is an operator (+ OR - OR * OR / OR %)
#define IS_OP(c) (IS_SIGN(c) || IS_MUL_DIV(c))

// Get the absolute value of a number
#define ABS(x) ((x) >= 0 ? (x) : -(x))

// Get the biggest of two numbers
#define MAX(x, y) ((x) > (y) ? (x) : (y))

// Get the smallest of two numbers
#define MIN(x, y) ((x) > (y) ? (y) : (x))

// Check if 3 values are equal
#define EQUAL_3(x, y, z) ((x) == (y) && (y) == (z))

// One-liner to return value and execute any function(s)
// -- I.G. returning a specific value while printing an error string
#define RETURN(value, funcs...) return (0 ? : (funcs, value))


#endif /* __USED_MACROS_H__ */
//<===========================================================================>






//<===========================================================================>
// Essentials Static Constantes.
#ifndef _STATICS_CONST_RETURN_
#define _STATICS_CONST_RETURN_


// Necessary includes.
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

// Typdef for uint128_t
typedef __int128_t int128_t;
typedef __uint128_t uint128_t;


typedef char const * const * const  str3c_t;
typedef char const * const          str2c_t;
typedef char const *                str1c_t;
typedef char *                      str_t;


// Static Constants for functions Returns.
static const uint8_t ERROR = 84;
static const uint8_t NOT_VALID = -42;
static const uint8_t SUCCESS = 0;
__unused static const void *MALLOC_FAIL = NULL;
#define MALLOC_FAILED ((void *)MALLOC_FAIL)


#endif /* _STATICS_CONST_RETURN_ */
//<===========================================================================>
