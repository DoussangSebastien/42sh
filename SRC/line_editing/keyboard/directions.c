/*
** EPITECH PROJECT, 2025
** keyboard
** File description:
** directions.c
*/

#include <unistd.h>
#include "../line.h"

int right(int *pos)
{
    if (!pos)
        return FAILURE;
    write(STDOUT_FILENO, "\x1b[C", 3);
    (*pos)++;
    return SUCCESS;
}

int left(int *pos)
{
    if (!pos)
        return FAILURE;
    write(STDOUT_FILENO, "\x1b[D", 3);
    (*pos)--;
    return SUCCESS;
}
