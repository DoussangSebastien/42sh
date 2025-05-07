/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** exit_functions.c
*/

#include "shell_protos.h"

int my_exit(args_t *args)
{
    int ret = 0;

    if (!args)
        return ERROR;
    if (args->tab[1])
        ret = my_getnbr(args->tab[1]);
    args->exit = 1;
    return ret;
}
