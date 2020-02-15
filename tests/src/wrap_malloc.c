/*
** EPITECH PROJECT, 2019
** Any project.
** File description:
** Wrapping malloc for unit tests purposes.
*/

#include <errno.h>
#include "my_malloc.h"
#include "internal.h"
#include "tests_run.h"

Test(sizecontrol, small_size_control_17)
{
    ASSERT_INT(align(17), 32);
}

Test(sizecontrol, small_size_control_8)
{
    ASSERT_INT(align(8), 16);
}

Test(sizecontrol, small_size_control_25)
{
    ASSERT_INT(align(25), 32);
}

Test(sizecontrol, small_size_control_32)
{
    ASSERT_INT(align(32), 64);
}
