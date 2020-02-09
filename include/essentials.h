/*
** EPITECH PROJECT, 2019
** any_project
** File description:
** Essentials Functions of Lib C.
*/

//<===============================================>
//<===============================================>
// Essentials Defines.
#ifndef UNUSED
#define UNUSED __attribute__((unused))
#endif /* UNUSED */

#ifndef HIDDEN
#define HIDDEN __attribute__((visibility ("hidden")))
#endif /* HIDDEN */

#ifndef DESTRUCTOR
#define DESTRUCTOR __attribute__((destructor))
#endif /* DESTRUCTOR */

#ifndef CONSTRUCTOR
#define CONSTRUCTOR __attribute__((constructor))
#endif /* CONSTRUCTOR */

//<===============================================>
//<===============================================>
// Essentials Static Constantes.
#ifndef _STATICS_CONST_RETURN_
#define _STATICS_CONST_RETURN_
#include <stddef.h>
static const int ERROR = 84;
static const int NOT_VALID = -42;
static const int SUCCESS = 0;
UNUSED static const void *MALLOC_FAILED = NULL;

//<===============================================>
//<===============================================>
// Essentials Static Constantes for strcmp/strncmp/strcmp_alpha/..only_alpha.
static const int S1_LONGER = 1;
static const int S2_LONGER = 2;
static const int S1_UPPER = -1;
static const int S2_UPPER = -2;
static const int EQUAL = 0;

#endif /* _STATICS_CONST_RETURN_ */
