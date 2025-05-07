/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** unalias_function.c
*/

#include "shell_protos.h"

static int lookup_variable(args_t *args, const char *name)
{
    alias_t *current = args->alias;
    alias_t *prev = NULL;
    int deleted = SUCCESS;
    alias_t *next = NULL;

    while (current) {
        if (!strcmp(name, current->name)) {
            next = current->next;
            del_alias(&current, prev, &args->alias);
            deleted = SUCCESS;
            current = next;
        } else {
            prev = current;
            current = current->next;
        }
    }
    return deleted;
}

int my_unalias(args_t *args)
{
    if (!args || !args->tab || !args->tab[0] || !args->tab[1])
        return fprintf(stderr, "unalias: Too few arguments.\n"), ERROR;
    if (args->tab[2]) {
        fprintf(stderr, "unalias: Too many arguments.\n");
        return ERROR;
    }
    return lookup_variable(args, args->tab[1]);
}
