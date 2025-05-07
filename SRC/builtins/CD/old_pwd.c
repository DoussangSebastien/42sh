/*
** EPITECH PROJECT, 2024
** edgar
** File description:
** old_pwd.c
*/

#include "shell_protos.h"

static int change_dir(environ_t *current)
{
    if (my_strstr(current->variable, "OLDPWD=")) {
        if (chdir(&current->variable[7]) == -1) {
            return 1;
        }
        return 0;
    }
    return 1;
}

int old_pwd(args_t *args)
{
    environ_t *current = NULL;
    int result = 1;

    if (!args)
        return ERROR;
    current = args->environ;
    while (current && result == 1) {
        result = change_dir(current);
        current = current->next;
    }
    return result;
}
