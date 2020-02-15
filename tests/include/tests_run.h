/*
** EPITECH PROJECT, 2019
** Any Project
** File description:
** Header for Unit Test using criterion.
*/

#ifndef __TESTS_RUN_H__
#define __TESTS_RUN_H__

#ifdef TESTS_RUN
#define static
#endif /* TESTS_RUN */

#include <criterion/criterion.h>
#include <criterion/redirect.h>


static inline void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}
#define ASSERT_INT(a, b) cr_assert_eq(a, b, "Expected %d, got %d\n", b, a)

#endif /* __TESTS_RUN_H__ */
